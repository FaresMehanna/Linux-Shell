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
typedef enum {
    executor_NOOP, executor_DONE, executor_ERR
} executor_state;

/**
* Function: execute
* ---------------
* try to execute the given command by giving the command to every exectuer.
*/
executor_state execute(SlinkedList *parameters);


#endif

