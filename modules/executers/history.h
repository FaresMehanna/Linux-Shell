/** 
 * File: history.h
 * ---------------
 */
#ifndef _EXECUTER_MODULE_HISTORY_
#define _EXECUTER_MODULE_HISTORY_

#include "executers_handler.h"
#include "../../datastructures/SingleLinkedList/SingleLinkedList.h"


 /** 
 * Function: historyShell
 * ---------------
 * if the given command is history, this will print all the commands.
 */
static inline executor_state historyShell(SlinkedList* parameters);


 #endif
