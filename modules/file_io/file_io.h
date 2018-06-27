/** 
 * File: file_io.h
 * ---------------
 * Defines the interface for the file I/O module.
 *
 * This module handles files.
 */
#ifndef file_io_h
#define file_io_h

/** 
 * Type: _file_io_state
 * ---------------
 * state of the operation, this is the return type for all the functions.
 */
typedef enum {
    file_io_success, file_io_last_line, file_io_memory_error, file_io_input_error,
    file_io_file_not_found
} FileIOState;


struct FileData {
    FILE *fp;
};

/**
* Function: read_file
* ---------------
* read the data from file line by line.
*
* file => pointer to fileDate struct.
* line => pointer to char* which will be pointing to the line.
*/
FileIOState read_file(struct FileData *file, char **line);

/**
* Function: set_file
* ---------------
* open the file.
*
* file => pointer to FileData struct.
* destination => path to wanted file to be read.
*/
FileIOState set_file(struct FileData *file, char *destination_line);

/**
* Function: close_file
* ---------------
* close the file.
*
* file => pointer to fileDate struct.
*/
FileIOState close_file(struct FileData *file);

#endif
