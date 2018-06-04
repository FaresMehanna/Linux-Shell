/** 
 * File: textio.h
 * ---------------
 * Defines the interface for the text I/O module.
 *
 * This module handles stdin/stdout.
 */
#ifndef _TEXTIO_MODULE_
#define _TEXTIO_MODULE_


/**
 * Type: _text_io_state
 * ---------------
 * state of the operation, this is the return type for all the functions.
 */
typedef enum {
    _text_io_SUCC, _text_io_MEMERR, _text_io_ERR, _text_io_SUCC_DONE
} _text_io_state;

/** 
 * Function: readNextLine
 * ---------------
 * read the buffer from stdin.
 *
 * destination => will point to malloced string, user responsibility to free the data.
 */
_text_io_state readNextLine(char **destination, FILE *ptr);


/** 
 * Function: getParameters
 * ---------------
 * given un-intialized SlinkedList it will convert the string into parameters.
 *
 * parameters => points to SlinkedList which will supports char* as it's value.
 */
_text_io_state getParameters(char *line, SlinkedList *parameters);


/** 
 * Function: printLine
 * ---------------
 * print given line to screen.
 *
 * line => points to string which will be printed.
 * freeB => flag to indicate wether the function should free the line or not.
 */
_text_io_state printLine(char *line, int freeB);

#endif
