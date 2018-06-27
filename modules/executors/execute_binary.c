//Language Libraries
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//System Libraries
#include <sys/wait.h>

//Data structures
#include "../../datastructures/singly_linked_list/singly_linked_list.h"

//Modules
#include "execute_binary.h"
#include "executors_handler.h"
#include "../text_io/string.h"
#include "../file_io/logger.h"
#include "../shell_io/shell_io.h"
#include "../directories_handler/current_directory_handler.h"

static inline char* handle_full_path_execution(SinglyLinkedList *parameters){

    char *binaryName;
    singly_linked_list_peek_front(parameters, &binaryName);
    int length = strlen(binaryName);

    //handle full path given
    if (binaryName[0] == '/') {

        if (access(binaryName, F_OK) == 0) {
            return binaryName;
        }
    }

    return NULL;
}

static inline char* handle_in_directory_execution(SinglyLinkedList *parameters){

    char *binaryName;
    singly_linked_list_peek_front(parameters, &binaryName);
    int length = strlen(binaryName);

    //handle ./execution
    if (length >= 2 && binaryName[0] == '.' && binaryName[1] == '/') {

        int counter = 2;
        char *current_working_directory = get_current_working_directory();    //get current directory

        if (current_working_directory == NULL) {
            return NULL;
        }

        struct String path;    //string to build the path

        if (create_string_from_char_array(&path, current_working_directory) != text_io_success) {
            return NULL;    //create the string from the curr directories_handler
        }

        //add the words to the string
        if (add_char_to_string(&path, '/') != text_io_success) {
            return NULL;
        }

        while (binaryName[counter] != '\0') {
            if (add_char_to_string(&path, binaryName[counter++]) != text_io_success) {
                return NULL;
            }
        }

        //get the string and return it
        char *full_path;
        trim_to_actual_size(&path);
        get_char_pointer(&path, &full_path);

        return binaryName;
    }

    return NULL;
}

static inline char* handle_in_PATH_execution(SinglyLinkedList *parameters){

    char *binaryName;
    singly_linked_list_peek_front(parameters, &binaryName);
    int length = strlen(binaryName);

    //TRY to get PATH from $PATH
    char *PATH_from_environment = getenv("PATH");
    if (!PATH_from_environment) {
        return NULL;
    }

    char *PATH_environment_clone = clone_string(PATH_from_environment);
    if(!PATH_environment_clone){
        return NULL;
    }

    char *single_path;
    single_path = strtok(PATH_environment_clone, ":");

    while (single_path != NULL) {

        int counter = 0;
        struct String path;

        if (create_string_from_char_array(&path, single_path) != text_io_success) {
            return NULL;
        }

        add_char_to_string(&path, '/');
        while (binaryName[counter] != '\0') {
            if (add_char_to_string(&path, binaryName[counter++]) != text_io_success) {
                return NULL;
            }
        }

        char *full_path;
        trim_to_actual_size(&path);
        get_char_pointer(&path, &full_path);

        if (access(full_path, F_OK) == 0) {
            return full_path;
        }

        single_path = strtok(NULL, ":");
    }

    return NULL;
}

static inline char *get_full_path(SinglyLinkedList *parameters) {

    char* result;

    result = handle_full_path_execution(parameters);
    if(result){
        return result;
    }

    result = handle_in_directory_execution(parameters);
    if(result){
        return result;
    }

    result = handle_in_PATH_execution(parameters);
    if(result){
        return result;
    }

    return NULL;
}

static inline void execute_with_execv(char *path, char **params, int background) {

    pid_t pid = fork();
    int status;

    if (pid == 0) {

        execv(path, params);
        print_to_user("Execution module - CHILD PROCESS", "CAN'T FORK", shell_error_message);
        exit(EXIT_FAILURE);

    } else if (pid > 0) {

        //log creation of the process
        char buff[128];
        sprintf(buff, "Child %d did start.", pid);

        if (write_to_log(buff) == log_io_file_error) {
            print_to_user("Execution module", "LOG FILE ISN'T ACCESSIBLE", shell_warning_message);
        }

        if (!background) {

            //wait child
            do {
                waitpid(pid, &status, WUNTRACED);
            } while (!WIFEXITED(status) && !WIFSIGNALED(status));

        } else {
            print_to_user("Execution module", "CHILD PROCESS STARTED IN BACKGROUND", shell_info_message);
        }

    } else {
        print_to_user("Execution module - PARENT PROCESS", "CAN'T FORK", shell_error_message);
    }
}

ExecutorState execute_binary(SinglyLinkedList *parameters) {

    //get the current path
    char *full_path = get_full_path(parameters);
    if (!full_path) {
        return executor_not_supported;
    }

    //make sure this is valid path
    if (access(full_path, F_OK) != 0) {
        print_to_user("Execution module", "Can not find this file", shell_error_message);
        return executor_error;
    }

    int back_ground_execution = 0;
    char *last_word_in_line;

    //check if it is meant to run in the background
    singly_linked_list_peek_back(parameters, &last_word_in_line);
    if (string_equal(last_word_in_line, "&")) {
        back_ground_execution = 1;
    }

    char *params[singly_linked_list_size(parameters) - back_ground_execution + 1];

    SinglyLinkedListIterator it;
    singly_linked_list_get_iterator(parameters, &it);
    int counter = 0;

    //get the parameter list for execv function
    while (singly_linked_list_iterator_has_next(&it)) {

        char *curr;
        singly_linked_list_iterator_get_next(&it, &curr);
        params[counter++] = curr;

        singly_linked_list_iterator_go_next(&it);
    }
    params[counter - back_ground_execution] = NULL;

    //execute the new process
    execute_with_execv(full_path, params, back_ground_execution);

    return executor_supported;
}