/** 
 * File: memory_manager.h
 * ---------------
 * Defines the interface for the memory manager module.
 *
 * This module handles memory operations.
 */
#ifndef memory_manager_h
#define memory_manager_h

//Language Libraries
#include <stdio.h>

//Data Structures Libraries
#include "../../datastructures/singly_linked_list/singly_linked_list.h"

struct Memory {
    SinglyLinkedList *map;
};

//since this is global variable. then map will be NULL initially.
struct Memory Global_Memory_Storage;

/**
* Function: smalloc
* ---------------
* malloc the needed size of bytes and return the address
*/
void *smalloc(size_t size);

/**
* Function: sfree
* ---------------
* free the give pointer of data
*/
void sfree(void *ptr);

/**
* Function: memory_clear
* ---------------
* clear all the malloced data
*/
void memory_clear();

/**
* Function: srealloc
* ---------------
* re alloc the memory to different size.
*/
void *srealloc(void *ptr, uint64_t newSize);

#endif
