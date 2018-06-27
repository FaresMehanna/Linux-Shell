/** 
 * File: shell_io.h
 * ---------------
 * Defines the interface for the shell I/O module.
 *
 * This module handles stdin/stdout.
 */
#ifndef shell_io_module_h
#define shell_io_module_h

//Data structure
#include "../../datastructures/singly_linked_list/singly_linked_list.h"

/** 
 * Type: ShellIOState
 * ---------------
 * state of the operation, this is the return type for all the functions.
 */
typedef enum {
    shell_io_success, shell_io_memory_error, shell_io_last_line,
    shell_io_length_exceeded, shell_io_error
} ShellIOState;

/**
 * Type: shellIOMessageType
 * ---------------
 * The types of accepted messages to be printed to the user.
 */
typedef enum {
    shell_info_message, shell_warning_message,
    shell_error_message
} shellIOMessageType;


/**
* Function: get_input_from_user
* ---------------
* read the buffer from stdin,
  given an uninitialized SinglyLinkedList it will convert the string into parameters.
*
* parameters => points to SinglyLinkedList which will supports char* as it's values.
*/
ShellIOState get_input_from_user(SinglyLinkedList *parameters);


/**
* Function: substitute_variables
* ---------------
* return shell_io_success substitute given variables in the char*.
*
* line => pointer to a pointer to the string.
*/
ShellIOState substitute_variables(char **line);


/** 
 * Function: print_to_user
 * ---------------
 * given a message, this will format and print the message.
 */
ShellIOState print_to_user(char *identifier, char *message, shellIOMessageType type);

#endif