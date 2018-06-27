//Language Libraries
#include <stdio.h>
#include <stdlib.h>

//Data structures
#include "../../datastructures/singly_linked_list/singly_linked_list.h"

//Modules
#include "exit.h"
#include "executors_handler.h"
#include "../text_io/string.h"
#include "../memory_manager/memory_manager.h"

ExecutorState exit_shell(SinglyLinkedList *parameters) {

    if (singly_linked_list_size(parameters) != 1) {
        return executor_not_supported;
    }

    char *first_word;
    singly_linked_list_peek_front(parameters, &first_word);

    //exit
    if (string_equal(first_word, "exit")) {
        printf("\nBye\n");
        memory_clear();
        exit(0);
    }

    return executor_not_supported;
}