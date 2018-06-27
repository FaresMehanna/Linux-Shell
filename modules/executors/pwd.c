//Language Libraries
#include <stdio.h>

//Data Structures
#include "../../datastructures/singly_linked_list/singly_linked_list.h"

//Modules
#include "executors_handler.h"
#include "../text_io/string.h"
#include "../directories_handler/current_directory_handler.h"

ExecutorState pwd(SinglyLinkedList *parameters) {

    if (singly_linked_list_size(parameters) != 1) {
        return executor_not_supported;
    }

    char *first_word;
    singly_linked_list_peek_front(parameters, &first_word);

    //execute the instruction if only one word and it's equal "pwd".
    if (string_equal(first_word, "pwd")) {

        char *current_working_directory = get_current_working_directory();

        if (current_working_directory != NULL) {
            printf("%s\n", current_working_directory);
        }else{
            return executor_error;
        }

        return executor_supported;
    }

    return executor_not_supported;
}