//Language Libraries
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

//Data structures
#include "../../datastructures/singly_linked_list/singly_linked_list.h"

//Modules
#include "expressions_evaluator.h"
#include "executors_handler.h"
#include "../text_io/string.h"
#include "../shell_io/shell_io.h"

static inline uint32_t is_valid_key(char* key){

    uint32_t length = strlen(key);

    for (uint32_t i = 0; i < length; i++) {

        if (key[i] >= 'a' && key[i] <= 'z') {
            continue;
        }

        if (key[i] >= 'A' && key[i] <= 'Z') {
            continue;
        }

        if (i && key[i] >= '0' && key[i] <= '9') {
            continue;
        }

        return 0;
    }

    return 1;
}

ExecutorState expressions_evaluator(SinglyLinkedList *parameters) {

    //get the first word
    char *first_word;
    singly_linked_list_peek_front(parameters, &first_word);

    //export used
    if (singly_linked_list_size(parameters) == 2) {

        //set the expression to the second argument
        if (string_equal(first_word, "export")) {
            singly_linked_list_peek_back(parameters, &first_word);
        } else {
            return executor_not_supported;
        }

    } else if (singly_linked_list_size(parameters) != 1) {        //expression only in one word
        return executor_not_supported;
    }

    //make a clone from the word
    char *clone = clone_string(first_word);
    uint32_t old_length = strlen(clone);

    //get the key
    char *key = strtok(clone, "=");
    if (key == NULL) {
        return executor_error;
    }

    key = clone_string(key);
    if (!is_valid_key(key)) {
        return executor_error;
    }

    //check the value
    uint32_t key_length = strlen(key);
    char *value;

    if (old_length == key_length) {
        return executor_error;
    } else if (old_length == key_length + 1) {
        value = clone_string("");
    } else {
        value = first_word + strlen(key) + 1;
    }

    substitute_variables(&value);

    //add to the env variables
    print_to_user("EXPRESSIONS EXECUTOR", "New variable has been defined.", shell_info_message);

    setenv(key, value, 1);

    //return done
    return executor_supported;
}