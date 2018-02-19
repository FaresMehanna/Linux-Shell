/** 
 * File: batch.h
 * ---------------
 * Defines the interface for the batch mode module.
 *
 * This module handles batch mode.
 */
#ifndef _BATCH_MODE_MODULE_
#define _BATCH_MODE_MODULE_

/** 
 * Type: _batch_mode_state
 * ---------------
 * state of the operation, this is the return type for all the functions.
 */
typedef enum{_batch_mode_SUCC, _batch_mode_MEMERR, _batch_mode_FILEERR} _batch_mode_state;


 /** 
 * Function: startBatchMode
 * ---------------
 * read line after line from user and execute it.
   with executors.
 */
_batch_mode_state startBatchMode(char* file);

 #endif
