/** 
 * File: change_directory.h
 * ---------------
 */
#ifndef executor_change_directory_h
#define executor_change_directory_h

//Data Structures Libraries
#include "../../datastructures/singly_linked_list/singly_linked_list.h"

//Modules Libraries
#include "executors_handler.h"

/**
* Function: change_directory
* ---------------
* if the given command is cd, this will change the current directory.
*/
ExecutorState change_directory(SinglyLinkedList *parameters);


#endif
