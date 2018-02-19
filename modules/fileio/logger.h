/** 
 * File: logger.h
 * ---------------
 * Defines the interface for the logger.
 *
 * This module handles log file.
 */
#ifndef _FILEIO_MODULE_LOGGER_
#define _FILEIO_MODULE_LOGGER_

/** 
 * Type: _log_io_state
 * ---------------
 * state of the operation, this is the return type for all the functions.
 */
typedef enum{_log_io_SUCC, _log_io_FILE_ERR} _log_io_state;

 /** 
 * Function: writeToLog
 * ---------------
 * write line to the log file.
 */
_log_io_state writeToLog(char* line);

 #endif
