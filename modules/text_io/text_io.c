//Language Libraries
#include <string.h>

//Data Structures
#include "../../datastructures/singly_linked_list/singly_linked_list.h"

//Modules
#include "text_io.h"
#include "string.h"
#include "../memory_manager/memory_manager.h"

TextIOState read_next_line(char **destination, FILE *ptr) {

    // growable buffer for characters
    char *buffer = NULL;
    // capacity of buffer
    int capacity = 0;
    // number of characters actually in buffer
    int size = 0;
    // max num of characters
    int size_max = 512000;
    // character read or EOF
    int c;

    //NULL file
    if (!ptr) {
        return text_io_error;
    }

    *destination = smalloc(sizeof(char));
    **destination = '\0';

    // iteratively get characters from standard input, checking for CR (Mac OS), LF (Linux), and CRLF (Windows)
    while ((c = fgetc(ptr)) != '\r' && c != '\n' && c != EOF) {
        // grow buffer if necessary
        if (size + 1 > capacity) {
            // initialize capacity to 16 (as reasonable for most inputs) and double thereafter
            if (capacity == 0) {
                capacity = 16;
            } else if (capacity <= (size_max / 2)) {
                capacity *= 2;
            } else if (capacity < size_max) {
                capacity = size_max;
            } else {
                sfree(buffer);
                return text_io_memory_error;
            }

            // extend buffer's capacity
            char *temp = srealloc(buffer, capacity);
            if (temp == NULL) {
                sfree(buffer);
                return text_io_memory_error;
            }
            buffer = temp;
        }

        // append current character to buffer
        buffer[size++] = c;
    }

    if (c == EOF) {
        if (size != 0) *destination = buffer;
        return text_io_last_line;
    }
    if (size == 0) {
        return text_io_success;
    }
    if (size == size_max) {
        sfree(buffer);
        return text_io_error;
    }
    char *to_return = srealloc(buffer, size + 1);
    if (!to_return) {
        return text_io_memory_error;
    }

    to_return[size] = '\0';
    *destination = to_return;

    return text_io_success;
}

static void free_string_for_list(void *string_word) {
    free(*(char **) string_word);
}

static inline TextIOState add_string_to_linked_list(struct String *current_word, SinglyLinkedList *parameters) {

    char *to_send;
    if (trim_to_actual_size(current_word) != text_io_success) {
        return text_io_memory_error; //remove any un-needed space
    }

    get_char_pointer(current_word, &to_send);  //get pointer to char*
    if (strlen(to_send) != 0) {
        if (singly_linked_list_add_back(parameters, &to_send) != singly_linked_list_succeed) {
            return text_io_memory_error; //add to parameter list
        }
    }

    if (create_string(current_word) != text_io_success) {
        return text_io_memory_error; //create new string
    }

    return text_io_success;
}

TextIOState get_parameters(char *line, SinglyLinkedList *parameters){

    //initalize the n list
    if (initialize_singly_linked_list(parameters, sizeof(char *), free_string_for_list, smalloc, sfree) != singly_linked_list_succeed) {
        return text_io_memory_error;
    }

    //pointer & flag
    int in_word = 0;
    int current_index = 0;
    int in_double_qoutation = 0;

    //build the string
    struct String current_word;
    create_string(&current_word);

    while (line[current_index] != '\0') {

        switch (line[current_index]) {

            case ' ':

                if (!in_word) {
                    break;
                }

                if (in_word && in_double_qoutation) {
                    if (add_char_to_string(&current_word, line[current_index]) != text_io_success) {
                        return text_io_memory_error;
                    }

                    break;
                }

                if (add_string_to_linked_list(&current_word, parameters) != text_io_success) {
                    return text_io_memory_error;
                }
                in_word = 0;    //set flag to new word
                break;


            case '"':

                in_word = 1;
                in_double_qoutation = in_double_qoutation == 0;
                break;

            default:
                in_word = 1;
                if (add_char_to_string(&current_word, line[current_index]) != text_io_success) {
                    return text_io_memory_error;
                }
                break;
        }
        current_index++;
    }

    //last word
    if (in_word && add_string_to_linked_list(&current_word, parameters) != text_io_success) {
        return text_io_memory_error;
    }

    return text_io_success;
}