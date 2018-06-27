/** 
 * File: history.h
 * ---------------
 */
#ifndef executor_history_h
#define executor_history_h

//Data Structures Libraries
#include "../../datastructures/singly_linked_list/singly_linked_list.h"

//Modules Libraries
#include "executors_handler.h"

/**
* Function: historyShell
* ---------------
* this function must be called on every command  to be stored in the history log.
* if the given command is history, this will print all the commands.
*/
ExecutorState history(SinglyLinkedList *parameters);


#endif
