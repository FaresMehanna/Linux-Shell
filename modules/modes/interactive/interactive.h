/** 
 * File: interactive.h
 * ---------------
 * Defines the interface for the interactive mode module.
 *
 * This module handles interactive mode.
 */
#ifndef _interactive_MODE_MODULE_
#define _interactive_MODE_MODULE_

/** 
 * Type: _interactive_mode_state
 * ---------------
 * state of the operation, this is the return type for all the functions.
 */
typedef enum{_interactive_mode_SUCC, _interactive_mode_MEMERR} _interactive_mode_state;


 /** 
 * Function: startInteractiveMode
 * ---------------
 * read line after line from user and execute it.
   with executors.
 */
_interactive_mode_state startInteractiveMode();

 #endif
