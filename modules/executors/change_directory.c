//Data structures
#include "../../datastructures/singly_linked_list/singly_linked_list.h"

//Modules
#include "change_directory.h"
#include "../directories_handler/current_directory_handler.h"
#include "../text_io/string.h"

ExecutorState change_directory(SinglyLinkedList *parameters) {

    //only two parameters, the "cd" and the wanted directory
    if (singly_linked_list_size(parameters) == 2) {

        //get the first parameter
        char *first_word;
        singly_linked_list_peek_front(parameters, &first_word);

        //check if it's cd
        if (!string_equal(first_word, "cd")) {
            return executor_not_supported;
        }

        //get the wanted directories_handler
        char *current_directory;
        singly_linked_list_peek_back(parameters, &current_directory);

        //change the directory
        if (set_new_current_working_directory(current_directory) == current_directory_handler_succeed) {
            return executor_supported;
        } else {
            return executor_error;
        }
    }

    return executor_not_supported;
}