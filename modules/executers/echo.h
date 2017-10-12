/** 
 * File: echo.h
 * ---------------
 */
#ifndef _EXECUTER_MODULE_ECHO_
#define _EXECUTER_MODULE_ECHO_

#include "executers_handler.h"
#include "../../datastructures/SingleLinkedList/SingleLinkedList.h"


 /** 
 * Function: echoShell
 * ---------------
 * if the given command is echo this function will print it to the user.
 */
static inline executor_state echoShell(SlinkedList* parameters);


 #endif
