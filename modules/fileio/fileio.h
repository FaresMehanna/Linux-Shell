/** 
 * File: fileio.h
 * ---------------
 * Defines the interface for the file I/O module.
 *
 * This module handles files.
 */
#ifndef _FILEIO_MODULE_
#define _FILEIO_MODULE_

/** 
 * Type: _file_io_state
 * ---------------
 * state of the operation, this is the return type for all the functions.
 */
typedef enum{_file_io_SUCC,_file_io_DONE, _file_io_MEMERR, _file_io_FILE_INPUTERR,
 _file_io_FILE_NFOUND} _file_io_state;


struct fileDate{
	FILE *fp;
};

 /** 
 * Function: readFile
 * ---------------
 * read the data from file line by line.
 *
 * file => pointer to fileDate struct.
 * line => pointer to char* which will be pointing to the line.
 */
_file_io_state readFile(struct fileDate* file, char** line);

 /** 
 * Function: setFile
 * ---------------
 * open the file.
 *
 * file => pointer to fileDate struct.
 * destination => path to wanted file to be read.
 */
_file_io_state setFile(struct fileDate* file, char* destination);

 /** 
 * Function: closeFile
 * ---------------
 * close the file.
 *
 * file => pointer to fileDate struct.
 */
_file_io_state closeFile(struct fileDate* file);

 #endif
