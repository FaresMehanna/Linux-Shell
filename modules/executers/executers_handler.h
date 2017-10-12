/** 
 * File: executers_handler.h
 * ---------------
 */
#ifndef _EXECUTER_MODULE_
#define _EXECUTER_MODULE_

 
/** 
 * Type: executor_state
 * ---------------
 * state of the operation, this is the return type for all the functions.
 */
typedef enum{executor_NOOP, executor_DONE, executor_ERR} executor_state;

#include "cd.h"
#include "echo.h"
#include "history.h"
#include "pwd.h"
#include "exit.h"
#include "execv.h"
#include "expressions.h"
#include "../../datastructures/SingleLinkedList/SingleLinkedList.h"

 /** 
 * Function: execute
 * ---------------
 * try to execute the given command by giving the command to every exectuer.
 */
static inline executor_state execute(SlinkedList* parameters);


 #endif

