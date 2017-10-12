/** 
 * File: dirs.h
 * ---------------
 * Defines the interface for the directory module.
 *
 * This module handles directories movement and listing.
 */
#ifndef _DIRS_MODULE_
#define _DIRS_MODULE_


/** 
 * Type: _dir_state
 * ---------------
 * state of the operation, this is the return type for all the functions.
 */
typedef enum{_dir_SUCC, _dir_MEMERR, _dir_NFOUND, _dir_ERR} _dir_state;


struct directoryData{
	struct string* currDir;
}directoryData;



 /** 
 * Function: getCurrDir
 * ---------------
 * return sMalloced string of the current directory.
 */
static inline char* getCurrDir();


 #endif
