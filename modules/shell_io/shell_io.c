//Language Libraries
#include <stdint.h>
#include <string.h>

//Data structures
#include "../../datastructures/singly_linked_list/singly_linked_list.h"

//Modules
#include "shell_io.h"
#include "../text_io/string.h"
#include "../text_io/text_io.h"

static inline ShellIOState is_valid_char(char character, uint32_t index){

    if (character >= 'a' && character <= 'z') {
        return shell_io_success;
    }

    if (character >= 'A' && character <= 'Z') {
        return shell_io_success;
    }

    if (index && character >= '0' && character <= '9') {
        return shell_io_success;
    }

    return shell_io_error;
}

ShellIOState get_input_from_user(SinglyLinkedList *parameters) {

    char *line;

    //handle any memory error
    TextIOState state = read_next_line(&line, stdin);

    substitute_variables(&line);

    if (state == text_io_last_line && feof(stdin)) {
        return shell_io_last_line;
    }

    if (state == text_io_error || state == text_io_memory_error) {
        return shell_io_memory_error;
    }

    uint32_t length = strlen(line);

    //handle big instructions
    if (length > 512) {
        return shell_io_length_exceeded;
    }

    //get the parameters
    if (get_parameters(line, parameters) != text_io_success) {
        return shell_io_memory_error;
    }

    return shell_io_success;
}


ShellIOState print_to_user(char *identifier, char *message, shellIOMessageType type){

    switch (type) {

        case shell_info_message:
            printf("INFO ::: ");
            break;

        case shell_warning_message:
            printf("WARNING ::: ");
            break;

        case shell_error_message:
            printf("ERROR ::: ");
            break;
    }

    printf("%s :: %s.\n", identifier, message);
    return shell_io_success;
}

static uint32_t handle_variable_declaration(char *execution_line, struct String *final_line, uint32_t index, uint32_t len) {

    struct String to_return;
    create_string(&to_return);

    uint32_t i;
    for (i = index; i < len; i++) {

        if (is_valid_char(execution_line[i], i - index) == shell_io_success) {
            add_char_to_string(&to_return, execution_line[i]);
        } else {
            break;
        }
    }

    uint32_t offset = i - index;
    char *variable_name;
    trim_to_actual_size(&to_return);
    get_char_pointer(&to_return, &variable_name);

    char *data = getenv(variable_name);
    if (data == NULL) {
        return offset;
    }

    i = 0;
    while (data[i++] != '\0') {
        add_char_to_string(final_line, data[i - 1]);
    }

    return offset;
}

ShellIOState substitute_variables(char **line){

    //get length and the string
    uint32_t len = strlen(*line);
    uint32_t temp_length;

    //create string to be manipulated and returned.
    struct String to_return;
    create_string(&to_return);

    char *current_line = *line;

    for (uint32_t i = 0; i < len; i++) {
        switch (current_line[i]) {

            case '$':

                if (i != 0 && current_line[i - 1] == '\\') {
                    add_char_to_string(&to_return, current_line[i]);
                    break;
                }

                temp_length = handle_variable_declaration(current_line, &to_return, i + 1, len);

                if (temp_length == 0) {
                    add_char_to_string(&to_return, current_line[i]);
                } else {
                    i += temp_length;
                }

                break;

            case '\\':
                break;

            case '~':

                //substitute with $HOME
                if (((int64_t)i - 1 >= 0 && current_line[i - 1] == ' ' && i + 1 == len) ||
                    ((int64_t)i - 1 >= 0 && current_line[i - 1] == ' ' && i + 1 < len && current_line[i + 1] == ' ') ||
                    ((int64_t)i - 1 >= 0 && current_line[i - 1] == ' ' && i + 1 < len && current_line[i + 1] == '/')) {

                    char *home_temp = getenv("HOME");
                    temp_length = 0;
                    while (home_temp[temp_length] != '\0') {
                        add_char_to_string(&to_return, home_temp[temp_length++]);
                    }

                } else {
                    add_char_to_string(&to_return, current_line[i]);
                }

                break;

            default:
                add_char_to_string(&to_return, current_line[i]);
                break;
        }
    }

    trim_to_actual_size(&to_return);
    get_char_pointer(&to_return, line);

    return shell_io_success;
}