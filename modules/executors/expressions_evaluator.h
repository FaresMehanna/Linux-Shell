/** 
 * File: expressions_evaluator.h
 * ---------------
 */
#ifndef executor_expressions_evaluator_h
#define executor_expressions_evaluator_h

//Data Structures Libraries
#include "../../datastructures/singly_linked_list/singly_linked_list.h"

//Modules Libraries
#include "executors_handler.h"

/**
* Function: expressions_evaluator
* ---------------
* if the given command is expressions, this function will evaluate and bind the data to the variable.
*/
ExecutorState expressions_evaluator(SinglyLinkedList *parameters);


#endif
