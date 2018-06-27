/** 
 * File: batch.h
 * ---------------
 * Defines the interface for the batch mode module.
 *
 * This module handles batch mode.
 */
#ifndef batch_mode_h
#define batch_mode_h

/** 
 * Type: BatchModeState
 * ---------------
 * state of the operation, this is the return type for all the functions.
 */
typedef enum {
    batch_mode_success, batch_mode_memory_error, batch_mode_file_error
} BatchModeState;


/**
* Function: start_batch_mode
* ---------------
* read line after line from user and execute it.
  with executors.
*/
BatchModeState start_batch_mode(char *file);

#endif
