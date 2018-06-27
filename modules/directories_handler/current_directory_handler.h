/** 
 * File: current_directory_handler.h
 * ---------------
 * Defines the interface for the directory module.
 *
 * This handler handles current working directory movement.
 */
#ifndef current_directory_handler_h
#define current_directory_handler_h

/**
 * Type: CurrentDirectoryHandlerState
 * ---------------
 * return type for the functions to get the result.
 *
 * current_directory_handler_succeed => in case of succeed in execution.
 * current_directory_handler_error => in case of error in execution.
 */
typedef enum {
    current_directory_handler_succeed, current_directory_handler_error
} CurrentDirectoryHandlerState;


/**
* Function: get_current_working_directory
* ---------------
* @return sMalloced string of the current directory.
*/
char *get_current_working_directory();


/**
* Function: set_new_current_working_directory
* ---------------
* Set the current directory with a new value.
*
*
* @return current_directory_handler_succeed in case of succeed in changing the current directory.
* @return current_directory_handler_error if an error happened.
*/
CurrentDirectoryHandlerState set_new_current_working_directory(char* new_working_directory);

#endif
