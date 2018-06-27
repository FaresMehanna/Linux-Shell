/** 
 * File: echo.h
 * ---------------
 */
#ifndef executor_echo_h
#define executor_echo_h

//Data Structures
#include "../../datastructures/singly_linked_list/singly_linked_list.h"

//Modules
#include "executors_handler.h"

/**
* Function: echoShell
* ---------------
* if the given command is echo this function will print it to the user.
*/
ExecutorState echo(SinglyLinkedList *parameters);


#endif
