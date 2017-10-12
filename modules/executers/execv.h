/** 
 * File: execv.h
 * ---------------
 */
#ifndef _EXECUTER_MODULE_EXECV_
#define _EXECUTER_MODULE_EXECV_

#include "executers_handler.h"
#include "../dir/dirs.h"
#include "../shellio/shellio.h"
#include "../textio/textio.h"
#include "../textio/string.h"
#include "../fileio/logger.h"
#include "../../datastructures/SingleLinkedList/SingleLinkedList.h"
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

 /** 
 * Function: execvShell
 * ---------------
 * if the given command is binary, this will execute the program.
 */
static inline executor_state execvShell(SlinkedList* parameters);


 #endif
