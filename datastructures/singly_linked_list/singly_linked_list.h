/** 
 * File: SinglyLinkedList.h
 * ---------------
 * Defines the interface for the Singly Linked List.
 *
 * This version of the Linked List allow the client to add generic item
 * to a signly list in Front or Back in constant time .
 * Extract data from front in O(1) and from back in O(N).
 * This DataStructure support Iterators
 */
#ifndef singly_linked_list_h
#define singly_linked_list_h

//Language Libraries
#include <stdint.h>
#include <stdlib.h>

/** 
 * Type: SinglyLinkedListState
 * ---------------
 * returns values for the function.
 *
 * singly_linked_list_succeed => if the operation succeeded.
 * singly_linked_list_memory_error => if memory error happens during the operation.
 * singly_linked_list_size_error => if the operation not allowed due to size of the list. As remove from empty list.
 * singly_linked_list_range_error => if the index parameter given to the function not in the allowed range by
 * the function.
 */
typedef enum {
    singly_linked_list_succeed, singly_linked_list_memory_error, singly_linked_list_range_error,
    singly_linked_list_size_error
} SinglyLinkedListState;

/** 
 * Type: ElementsCompareFunction
 * ---------------
 * Defines the Function needed to Search in the List.
 *
 * In case the client needs to search in the List in O(N), the client
 * must supply pointer to compare function that will take pointer to the key
 * and pointer to the element in the list and must return 1 in case of equality
 * or 0 otherwise.
 */
typedef int32_t (*ElementsCompareFunction)(void *, void *);


/** 
 * Type: ElementsFreeFunction
 * ---------------
 * Defines the Function needed to free the List's elements when needed.
 *
 * FreeFunction is pointer to client-supplied function to free the items
 * When dispose the List or when element need to be freed. the function will
 * receive one element at a time and its job to free it. client will need to use it
 * with all malloced variables, client will send NULL if it's in the stack.
 */
typedef void (*ElementsFreeFunction)(void *);


/** 
 * Type: SinglyLinkedListNode
 * ---------------
 * Defines the struct needed for the single node.
 *
 * Each node will have two field, pointer to the data and pointer to the
 * next node.
 */
typedef struct SinglyLinkedListNode {
    void *element;
    struct SinglyLinkedListNode *next;
} SinglyLinkedListNode;

/**
 * Type: MallocFunction, FreeFunction
 * ---------------
 * Defines the function needed to malloc and free the data from the heap.
 *
 * This function used to be the malloc() and free() in C. but user may use different functions
 * for malloc and free the data.
 */
typedef void *(*MallocFunction)(size_t);
typedef void (*FreeFunction)(void *);


/** 
 * Type: _singly_linked_list_
 * ---------------
 * Defines the struct needed for the Singly Linked List.
 *
 * size => size of the linked List.
 * elemSize => the size in Bytes for each element in the list.
 * elemFree => pointer to the client supplied function used when freeing the elements.
 * head => pointer to dummy node at the head.
 * end => pointer to last node in the List.
 * malloc, free => pointer the functions to be used to malloc() and free() the data in the linkedList.
 */
typedef struct SinglyLinkedList {

    uint64_t size;
    uint32_t element_size;

    ElementsFreeFunction element_free_function;

    SinglyLinkedListNode *head;
    SinglyLinkedListNode *end;

    MallocFunction malloc;
    FreeFunction free;

} SinglyLinkedList;

/** 
 * Type: SinglyLinkedListIterator
 * ---------------
 * Defines the struct needed for the iterator.
 *
 * list => pointer to the list which the iterator traverse.
 * node => pointer to the current node int32_t the list.
 */
typedef struct SinglyLinkedListIterator {
    SinglyLinkedList *list;
    SinglyLinkedListNode *node;
} SinglyLinkedListIterator;


/** 
 * Function: initialize_singly_linked_list
 * ---------------
 * Initialize the given LinkedList.
 *
 * list => pointer to the SinglyLinkedList.
 * element_size => the number of bytes for each element in the list.
 * ElementsFreeFunction => the function which will be used to free items when items no longer in use, Null should
 * be provided in case the elements don't need to be freed, as if it's stored in stack.
 * MallocFunction, FreeFunction => function to be used instead of malloc() and free(). If no special function
 * needed, just provide original malloc() and free() functions.
 */
SinglyLinkedListState initialize_singly_linked_list(SinglyLinkedList *list, uint32_t element_size, ElementsFreeFunction,
                                         MallocFunction, FreeFunction);    //O(1)

/** 
 * Function: dispose_singly_linked_list
 * ---------------
 * Dispose the given LinkedList.
 *
 * list => pointer to the SinglyLinkedList.
 */
SinglyLinkedListState dispose_singly_linked_list(SinglyLinkedList *list);    //O(N)

/** 
 * Function: singly_linked_list_add_front
 * ---------------
 * Add element to the start of the LinkedList.
 *
 * list => pointer to the SinglyLinkedList.
 * element_address => pointer to the item data.
 */
SinglyLinkedListState singly_linked_list_add_front(SinglyLinkedList *list, void *element_address);    //O(1)

/** 
 * Function: singly_linked_list_remove_front
 * ---------------
 * Remove element From the start of the LinkedList.
 *
 * list => pointer to the SinglyLinkedList.
 */
SinglyLinkedListState singly_linked_list_remove_front(SinglyLinkedList *list);    //O(1)

/** 
 * Function: singly_linked_list_peek_front
 * ---------------
 * write the first element from the LinkedList in target_address.
 *
 * list => pointer to the SinglyLinkedList.
 * target_address => pointer to the place in memory to write the data in it.
 */
SinglyLinkedListState singly_linked_list_peek_front(SinglyLinkedList *list, void *target_address);    //O(1)

/** 
 * Function: singly_linked_list_extract_front
 * ---------------
 * write the first element from the LinkedList in target_address AND remove the element.
 *
 * list => pointer to the SinglyLinkedList.
 * target_address => pointer to the place in memory to write the data in it.
 */
SinglyLinkedListState singly_linked_list_extract_front(SinglyLinkedList *list, void *target_address);    //O(1)

/** 
 * Function: singly_linked_list_add_back
 * ---------------
 * Add element to the end of the LinkedList.
 *
 * list => pointer to the SinglyLinkedList.
 * element_address => pointer to the item data to be copied in the list.
 */
SinglyLinkedListState singly_linked_list_add_back(SinglyLinkedList *list, void *element_address);    //O(1)

/** 
 * Function: singly_linked_list_remove_back
 * ---------------
 * Remove element From the end of the LinkedList.
 *
 * list => pointer to the SinglyLinkedList.
 */
SinglyLinkedListState singly_linked_list_remove_back(SinglyLinkedList *list);    //O(N)

/** 
 * Function: singly_linked_list_peek_back
 * ---------------
 * Write the last element from the LinkedList in target_address.
 *
 * list => pointer to the SinglyLinkedList.
 * target_address => pointer to the place in memory to write the data in it.
 */
SinglyLinkedListState singly_linked_list_peek_back(SinglyLinkedList *list, void *target_address);    //O(1)

/** 
 * Function: singly_linked_list_extract_back
 * ---------------
 * Write the last element from the LinkedList in target_address AND remove the element.
 *
 * list => pointer to the SinglyLinkedList.
 * target_address => pointer to the place in memory to write the data in it.
 */
SinglyLinkedListState singly_linked_list_extract_back(SinglyLinkedList *list, void *target_address);    //O(N)

/** 
 * Function: singly_linked_list_get
 * ---------------
 * Get the element with this index, the index is 0-based and must be smaller than the size.
 *
 * list => pointer to the SinglyLinkedList.
 * index => integer represents the index of the wanted element.
 * target_address => pointer to the place in memory to write the data in it.
 */
SinglyLinkedListState singly_linked_list_get(SinglyLinkedList *list, uint32_t index, void *target_address);    //O(N)

/** 
 * Function: singly_linked_list_remove
 * ---------------
 * Remove the element with this index, the index is 0-based and must be smaller than the size.
 *
 * list => pointer to the SinglyLinkedList.
 * index => integer represents the element wanted.
 */
SinglyLinkedListState singly_linked_list_remove(SinglyLinkedList *list, uint32_t index);    //O(N)

/** 
 * Function: singly_linked_list_insert
 * ---------------
 * Insert the element in this index, the index is 0-based and must be smaller than or equal the size.
 * '0' mean before the current start and 'size' mean after the current end.
 *
 * list => pointer to the SinglyLinkedList.
 * index => integer represents the index to insert the data in.
 * element_address => pointer to the place in memory to read the data from.
 */
SinglyLinkedListState singly_linked_list_insert(SinglyLinkedList *list, uint32_t index, void *element_address);    //O(N)

/** 
 * Function: singly_linked_list_search
 * ---------------
 * Search for specific key in the linked list. This only search for the first occurrence. If found
 * the index will be set to the first occurrence, else index will be -1.
 *
 * list => pointer to the SinglyLinkedList.
 * key_address => pointer to the key the client want to search.
 * ElementsCompareFunction => pointer to function to compare the key with every element.
 * index => is a pointer to the integer which the function will override its data to the location of the index.
 * If not found the index value will be -1.
 */
SinglyLinkedListState singly_linked_list_search(SinglyLinkedList *list, void *key_address, ElementsCompareFunction,
                                                uint32_t *index);    //O(N)

/** 
 * Function: singly_linked_list_size
 * ---------------
 * return the size of the LinkedList.
 *
 * @param list => pointer to the SinglyLinkedList
 */
uint64_t singly_linked_list_size(SinglyLinkedList *list);    //O(1)

/** 
 * Function: singly_linked_list_get_iterator
 * ---------------
 * initialized the iterator with the needed information.
 * The Iterator initially will be pointing to dummy Node.
 *
 * @param list => pointer to the SinglyLinkedList
 * @param iterator => this pointer to struct SinglyLinkedListIterator, and will be initialized with the needed information.
 */
void singly_linked_list_get_iterator(SinglyLinkedList *list, SinglyLinkedListIterator *iterator);    //O(1)

/** 
 * Function: singly_linked_list_iterator_get_current
 * ---------------
 * Write the current node's data to the target address.
 *
 * @param iterator => pointer to the SinglyLinkedListIterator.
 */
void singly_linked_list_iterator_get_current(SinglyLinkedListIterator *iterator, void *target_address);    //O(1)

/** 
 * Function: singly_linked_list_iterator_has_next
 * ---------------
 * Check if there is next node.
 * This function must be called after getting the iterator as the iterator at first pointing to dummy node.
 *
 * @param iterator => pointer to the Iterator.
 * @return 1 if there is node next, 0 otherwise.
 */
int32_t singly_linked_list_iterator_has_next(SinglyLinkedListIterator *iterator);    //O(1)

/** 
 * Function: singly_linked_list_iterator_get_next
 * ---------------
 * write the next node's data to the target_address.
 *
 * @param iterator => pointer to the Iterator.
 */
void singly_linked_list_iterator_get_next(SinglyLinkedListIterator *iterator, void *target_address);    //O(1)

/** 
 * Function singly_linked_list_iterator_go_next
 * ---------------
 * Advance the iterator to the forward.
 *
 * @param iterator => pointer to the Iterator.
 */
void singly_linked_list_iterator_go_next(SinglyLinkedListIterator *iterator);    //O(1)

#endif