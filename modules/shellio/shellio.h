/** 
 * File: shellio.h
 * ---------------
 * Defines the interface for the shell I/O module.
 *
 * This module handles stdin/stdout.
 */
#ifndef _SHELLIO_MODULE_
#define _SHELLIO_MODULE_

/** 
 * Type: _shell_io_state
 * ---------------
 * state of the operation, this is the return type for all the functions.
 */
typedef enum{_shell_io_SUCC, _shell_io_MEMERR, _shell_io_ERR,
 _shell_io_LENGTHEXCED,_shell_io_END} _shell_io_state;
typedef enum{_shell_io_msg_state_INFO, _shell_io_msg_state_WARNING,
 _shell_io_msg_state_ERROR} shell_io_msg_state;


 /** 
 * Function: getInputFromUser
 * ---------------
 * read the buffer from stdin, 
   given un-intialized SlinkedList it will convert the string into parameters.
 *
 * parameters => points to SlinkedList which will supports char* as it's values.
 */
_shell_io_state getInputFromUser(SlinkedList* parameters);


 /** 
 * Function: validateVarChar
 * ---------------
 * return _shell_io_SUCC if the char is valid, _shell_io_ERR otherwise.
 *
 * varCHar => the char to be tested.
 */
_shell_io_state validateVarChar(char varCHar, int index);

 /** 
 * Function: substitueVars
 * ---------------
 * return _shell_io_SUCC substitute given variables in the char*.
 *
 * str => pointer to the string to be handled.
 */
_shell_io_state substitueVars(char** varCHar);


/** 
 * Function: printToUser
 * ---------------
 * given a message this will format and print the message.
 */
_shell_io_state printToUser(char* identifier, char* message, shell_io_msg_state state, int o1, int o2);

 #endif
