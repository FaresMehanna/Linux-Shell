/** 
 * File: cd.h
 * ---------------
 */
#ifndef _EXECUTER_MODULE_CD_
#define _EXECUTER_MODULE_CD_

#include "executers_handler.h"
#include "../../datastructures/SingleLinkedList/SingleLinkedList.h"


 /** 
 * Function: cdShell
 * ---------------
 * if the given command is cd, this will change the current directory.
 */
static inline executor_state cdShell(SlinkedList* parameters);


 #endif
