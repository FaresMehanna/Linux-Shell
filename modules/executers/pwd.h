/** 
 * File: pwd.h
 * ---------------
 */
#ifndef _EXECUTER_MODULE_PWD_
#define _EXECUTER_MODULE_PWD_

#include "executers_handler.h"
#include "../../datastructures/SingleLinkedList/SingleLinkedList.h"


 /** 
 * Function: pwdShell
 * ---------------
 * if the given command is pwd, this will print the current directory.
 */
static inline executor_state pwdShell(SlinkedList* parameters);


 #endif
