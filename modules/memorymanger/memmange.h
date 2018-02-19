/** 
 * File: memmange.h
 * ---------------
 * Defines the interface for the memory mangement module.
 *
 * This module handles memory operations.
 */
#ifndef _MEMMANGE_MODULE_
#define _MEMMANGE_MODULE_
 
 struct mem{
 	HashmapChain* map;
 };

 struct mem GLOBAL_MEMORY_STORAGE_;

 /** 
 * Function: smalloc
 * ---------------
 * malloc the needed size of bytes and return the address
 */
void* smalloc(size_t size);

 /** 
 * Function: sfree
 * ---------------
 * free the give pointer of data
 */
void sfree(void* ptr);

 /** 
 * Function: memoryClear
 * ---------------
 * clear all the malloced data
 */
void memoryClear();

 /** 
 * Function: srealloc
 * ---------------
 * realloc the memory to different size.
 */
void* srealloc(void* ptr, size_t newSize);

 #endif
