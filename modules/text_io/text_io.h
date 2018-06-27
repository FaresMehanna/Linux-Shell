/** 
 * File: text_io.h
 * ---------------
 * Defines the interface for the text I/O module.
 *
 * This module handles stdin/stdout.
 */
#ifndef text_io_h
#define text_io_h

//Language Libraries
#include <stdio.h>

//Data Structures Libraries
#include "../../datastructures/singly_linked_list/singly_linked_list.h"

/**
 * Type: TextIOState
 * ---------------
 * state of the operation, this is the return type for all the functions.
 */
typedef enum {
    text_io_success, text_io_memory_error, text_io_error, text_io_last_line
} TextIOState;

/** 
 * Function: readNextLine
 * ---------------
 * read the buffer from stdin.
 *
 * destination => will point to malloced string, user responsibility to free the data.
 */
TextIOState read_next_line(char **destination, FILE *ptr);


/** 
 * Function: get_parameters
 * ---------------
 * given uninitialized SinglyLinkedList it will convert the string into parameters.
 *
 * parameters => points to SinglyLinkedList which will supports char* as it's value.
 */
TextIOState get_parameters(char *line, SinglyLinkedList *parameters);


/** 
 * Function: print_line
 * ---------------
 * print given line to screen.
 *
 * line => points to string which will be printed.
 * freeB => flag to indicate if the function should free the line or not.
 */
TextIOState print_line(char *line, int free_boolean);

#endif
