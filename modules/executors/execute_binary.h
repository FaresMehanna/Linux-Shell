/** 
 * File: execute_binary.h
 * ---------------
 */
#ifndef executor_execute_binary_h
#define executor_execute_binary_h

//Data Structures
#include "../../datastructures/singly_linked_list/singly_linked_list.h"

//Modules
#include "executors_handler.h"

/**
* Function: execute_binary
* ---------------
* if the given command is execute binary file, this will execute the program.
*/
ExecutorState execute_binary(SinglyLinkedList *parameters);


#endif
