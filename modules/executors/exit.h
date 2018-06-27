/** 
 * File: exit.h
 * ---------------
 */
#ifndef executor_exit_h
#define executor_exit_h

//Data Structures
#include "../../datastructures/singly_linked_list/singly_linked_list.h"

//Modules
#include "executors_handler.h"


/**
* Function: exit_shell
* ---------------
* if the given command is exit, this will terminate the program.
*/
ExecutorState exit_shell(SinglyLinkedList *parameters);


#endif
