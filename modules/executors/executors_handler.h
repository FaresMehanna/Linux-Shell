/** 
 * File: executors_handler.h
 * ---------------
 */
#ifndef executor_handler_h
#define executor_handler_h

//Data Structures Libraries
#include "../../datastructures/singly_linked_list/singly_linked_list.h"

/**
 * Type: executor_state
 * ---------------
 * state of the operation, this is the return type for all the functions.
 */
typedef enum {
    executor_not_supported, executor_supported, executor_error
} ExecutorState;

/**
* Function: execute
* ---------------
* try to execute the given command by giving the command to every exectuer.
*/
ExecutorState execute(SinglyLinkedList *parameters);


#endif

