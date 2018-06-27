/** 
 * File: logger.h
 * ---------------
 * Defines the interface for the logger.
 *
 * This module handles log file.
 */
#ifndef file_io_logger_h
#define file_io_logger_h

/** 
 * Type: _log_io_state
 * ---------------
 * state of the operation, this is the return type for all the functions.
 */
typedef enum {
    log_io_success, log_io_file_error
} LogIOState;

/**
* Function: write_to_log
* ---------------
* write line to the log file.
*/
LogIOState write_to_log(char *line);

#endif
