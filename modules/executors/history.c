//Language Libraries
#include <stdio.h>

//Data Structures
#include "../../datastructures/singly_linked_list/singly_linked_list.h"

//Modules
#include "executors_handler.h"
#include "../text_io/string.h"
#include "../file_io/file_io.h"

static inline ExecutorState history_write(SinglyLinkedList *parameters) {

    FILE *file_pointer;
    char buffer[1024];

    //get the path to the history file
    char *directory = getenv("1ShellHome");
    if (!directory) {
        return executor_error;
    }

    //get complete path
    sprintf(buffer, "%s/ShellHistory.txt", directory);

    //open the history file for appending
    file_pointer = fopen(buffer, "a");
    if (!file_pointer) {
        return executor_error;
    }

    //write the line to the history file
    SinglyLinkedListIterator it;
    singly_linked_list_get_iterator(parameters, &it);

    while (singly_linked_list_iterator_has_next(&it)) {
        char *curr;
        singly_linked_list_iterator_get_next(&it, &curr);
        singly_linked_list_iterator_go_next(&it);
        fprintf(file_pointer, "%s ", curr);
    }

    fprintf(file_pointer, "\n");

    //close and return success
    fclose(file_pointer);

    return executor_supported;
}

static inline ExecutorState history_read(SinglyLinkedList *parameters) {

    if (singly_linked_list_size(parameters) != 1) {
        return executor_not_supported;
    }

    char *first_word;
    singly_linked_list_peek_front(parameters, &first_word);

    //history
    if (!string_equal(first_word, "history")) {
        return executor_not_supported;
    }

    char buffer[1024];

    //get the path to the history file
    char *directory = getenv("1ShellHome");
    if (!directory) {
        return executor_error;
    }

    sprintf(buffer, "%s/ShellHistory.txt", directory);

    //try to read history if there is history
    struct FileData file;
    if (set_file(&file, buffer) != file_io_success) {
        return executor_supported;
    }

    //get input from the file
    char *current_line;
    while (read_file(&file, &current_line) == file_io_success) {
        printf("%s\n", current_line);
    }

    //close and return succ
    close_file(&file);

    return executor_supported;
}

ExecutorState history(SinglyLinkedList *parameters) {
    history_write(parameters);
    return history_read(parameters);
}