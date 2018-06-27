//Language Libraries
#include <stdio.h>

//Data structures
#include "../../datastructures/singly_linked_list/singly_linked_list.h"

//modules
#include "echo.h"
#include "executors_handler.h"
#include "../text_io/string.h"

ExecutorState echo(SinglyLinkedList *parameters) {

    char *first_word;
    singly_linked_list_peek_front(parameters, &first_word);

    //print the list
    if (string_equal(first_word, "echo")) {

        //iterator to the parameters list
        SinglyLinkedListIterator iterator;
        singly_linked_list_get_iterator(parameters, &iterator);
        singly_linked_list_iterator_go_next(&iterator);

        //print the given line
        while (singly_linked_list_iterator_has_next(&iterator)) {

            char *current;
            singly_linked_list_iterator_get_next(&iterator, &current);
            printf("%s ", current);

            singly_linked_list_iterator_go_next(&iterator);
        }

        printf("\n");

        return executor_supported;
    }

    return executor_not_supported;
}