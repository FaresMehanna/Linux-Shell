/** 
 * File: pwd.h
 * ---------------
 */
#ifndef executor_pwd_h
#define executor_pwd_h

//Data Structures Libraries
#include "../../datastructures/singly_linked_list/singly_linked_list.h"

//Modules Libraries
#include "executors_handler.h"

/**
* Function: pwdShell
* ---------------
* if the given command is pwd, this will print the current directory.
*/
ExecutorState pwd(SinglyLinkedList *parameters);


#endif
