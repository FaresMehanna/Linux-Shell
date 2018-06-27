/** 
 * File: interactive.h
 * ---------------
 * Defines the interface for the interactive mode module.
 *
 * This module handles interactive mode.
 */
#ifndef interactive_mode_h
#define interactive_mode_h

/** 
 * Type: InteractiveModeState
 * ---------------
 * state of the operation, this is the return type for all the functions.
 */
typedef enum {
    interactive_mode_success, interactive_mode_memory_error
} InteractiveModeState;


/**
* Function: start_interactive_mode
* ---------------
* read line after line from user and execute it.
  with executors.
*/
InteractiveModeState start_interactive_mode();

#endif
