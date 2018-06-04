/** 
 * File: SignleLinkedList.h
 * ---------------
 * Defines the interface for the Single Linked List.
 *
 * This version of the Linked List allow the client to add generic item
 * to a signle list in Front or Back in constant time .
 * Extract data from front in O(1) and from back in O(N).
 * this DataStructure support Iterators
 */
#ifndef _singlelinkedlist_
#define _singlelinkedlist_

/** 
 * Type: __SlinkedList_state
 * ---------------
 * state of the operation
 */
typedef enum {
    _SlinkedList_SUCC, _SlinkedList_MEMERR, _SlinkedList_SIZEERR
} _SlinkedList_state;

/** 
 * Type: CompareFunction
 * ---------------
 * Defines the Function needed to Search in the List
 *
 * Incase the client needed to search in the List in O(N), the client
 * must supply pointer to compare function that will take pointer to the key
 * and pointer to the element in the list and must return 1 in case of equality
 * or 0 otherwise.
 */
typedef int (*CompareFunction)(void *, void *);


/** 
 * Type: FreeFunction
 * ---------------
 * Defines the Function needed to free the List's element when needed
 *
 * FreeFunction is pointer to client-supplied function to free the items
 * When dispose the List or when element need to be freed. the function will
 * recieve one element at time and it's job to free it. client will need to use it 
 * with all malloced variable, client will send NULL if it's in the stack
 */
typedef void (*FreeFunction)(void *);


/** 
 * Type: Snode
 * ---------------
 * Defines the Struct needed for the Single node
 *
 * Each node will have two field, pointer to the data and pointer to the
 * next node 
 */
typedef struct Snode {
    void *element;
    struct Snode *next;
} Snode;

//memory abs
typedef void *(*mallocData)(size_t);

typedef void (*freeData)(void *);

/** 
 * Type: SlinkedList
 * ---------------
 * Defines the Struct needed for the Single Linked List
 *
 * size => size of the linked List
 * elemsize => the size in Byte for each element in the list
 * freeFN => pointer to client supplied function used when freeing the elements
 * head => pointer to dummy node at the head
 * end => pointer to last node in the List
 */
typedef struct SlinkedList {
    long long size;
    int elemsize;
    FreeFunction freeFN;
    Snode *head;
    Snode *end;
    mallocData MD;
    freeData FD;
} SlinkedList;

/** 
 * Type: SIterator
 * ---------------
 * Defines the Struct needed for the Iterator
 *
 * list => pointer to the List which the Iterator traverse
 * ndoe => pointer to the current node
 */
typedef struct SIterator {
    SlinkedList *list;
    Snode *node;
} SIterator;


/** 
 * Function: stateToMsg
 * ---------------
 * translate state to readable format.
 */
static inline char *stateToMsg(_SlinkedList_state state);

/** 
 * Function: InitializeSLinkedList
 * ---------------
 * Initialize the given LinkedList
 *
 * x => pointer to the SingleLinkedList
 * elementSize => the number of bytes for each element in the list
 * FreeFunction => the function which will be used to free items, NULL if items
 * is simple type as int,long,char,...
 */
_SlinkedList_state InitializeSLinkedList(SlinkedList *x, int elementSize, FreeFunction,
                                         mallocData MD, freeData FD);    //O(1)

/** 
 * Function: DisposeSLinkedList
 * ---------------
 * Dispose the given LinkedList
 *
 * x => pointer to the SingleLinkedList
 */
_SlinkedList_state DisposeSLinkedList(SlinkedList *x);    //O(N)

/** 
 * Function: SLinkedListAddFront
 * ---------------
 * Add element to the start of the LinkeList
 *
 * x => pointer to the SingleLinkedList
 * elementAddress => pointer to the item data
 */
_SlinkedList_state SLinkedListAddFront(SlinkedList *x, void *elementAddress);    //O(1)

/** 
 * Function: SLinkedListRemoveFront
 * ---------------
 * Remove element From the start of the LinkeList
 *
 * x => pointer to the SingleLinkedList
 */
_SlinkedList_state SLinkedListRemoveFront(SlinkedList *x);    //O(1)

/** 
 * Function: SLinkedListPeekFront
 * ---------------
 * write the first element from the LinkeList in targetAddress
 *
 * x => pointer to the SingleLinkedList
 * targetAddress => pointer to the place in memory to write the data in it
 */
_SlinkedList_state SLinkedListPeekFront(SlinkedList *x, void *targetAddress);    //O(1)

/** 
 * Function: SLinkedListExtractFront
 * ---------------
 * write the first element from the LinkeList in targetAddress AND remove the element
 *
 * x => pointer to the SingleLinkedList
 * targetAddress => pointer to the place in memory to write the data in it
 */
_SlinkedList_state SLinkedListExtractFront(SlinkedList *x, void *targetAddress);    //O(1)

/** 
 * Function: SLinkedListAddBack
 * ---------------
 * Add element to the end of the LinkeList
 *
 * x => pointer to the SingleLinkedList
 * elementAddress => pointer to the item data
 */
_SlinkedList_state SLinkedListAddBack(SlinkedList *x, void *elementAddress);    //O(1)

/** 
 * Function: SLinkedListRemoveback
 * ---------------
 * Remove element From the end of the LinkeList
 *
 * x => pointer to the SingleLinkedList
 */
_SlinkedList_state SLinkedListRemoveBack(SlinkedList *x);    //O(N)

/** 
 * Function: SLinkedListPeekBack
 * ---------------
 * write the last element from the LinkeList in targetAddress
 *
 * x => pointer to the SingleLinkedList
 * targetAddress => pointer to the place in memory to write the data in it
 */
_SlinkedList_state SLinkedListPeekBack(SlinkedList *x, void *targetAddress);    //O(1)

/** 
 * Function: SLinkedListExtractBack
 * ---------------
 * write the last element from the LinkeList in targetAddress AND remove the element
 *
 * x => pointer to the SingleLinkedList
 * targetAddress => pointer to the place in memory to write the data in it
 */
_SlinkedList_state SLinkedListExtractBack(SlinkedList *x, void *targetAddress);    //O(N)

/** 
 * Function: SLinkedListGet
 * ---------------
 * get the element with this index, the index is 0-based and must be < the size
 *
 * x => pointer to the SingleLinkedList
 * index => Integer represent the element wanted
 * targetAddress => pointer to the place in memory to write the data in it
 */
_SlinkedList_state SLinkedListGet(SlinkedList *x, int index, void *targetAddress);    //O(N)

/** 
 * Function: SLinkedListRemove
 * ---------------
 * Remove the element with this index, the index is 0-based and must be < the size
 *
 * x => pointer to the SingleLinkedList
 * index => Integer represent the element wanted
 */
_SlinkedList_state SLinkedListRemove(SlinkedList *x, int index);    //O(N)

/** 
 * Function: SLinkedListInsert
 * ---------------
 * Insert the element in this index, the index is 0-based and must be <= the size
 *
 * x => pointer to the SingleLinkedList
 * index => Integer represent the index to insert the data in
 * elementAddress => pointer to the place in memory to read the data from
 */
_SlinkedList_state SLinkedListInsert(SlinkedList *x, int index, void *elementAddress);    //O(N)

/** 
 * Function: SLinkedListSearch
 * ---------------
 * Search for specific key in the linked list
 *
 * x => pointer to the SingleLinkedList
 * keyAddress => pointer to the key the client want to search
 * CompareFunction => pointer to function to compare the key with every element
 * index => is a pointer to the integer which the function will override it's data to the location of the index
 * if not found the index value will be -1
 */
_SlinkedList_state SLinkedListSearch(SlinkedList *x, void *keyAddress, CompareFunction, int *index);    //O(N)

/** 
 * Function: SLinkedListSize
 * ---------------
 * return the size of the LinkedList
 */
long long SLinkedListSize(SlinkedList *x);    //O(1)

/** 
 * Function: SLinkedListGetIterator
 * ---------------
 * Return pointer to the Iterator
 * the Iterator initialy will be pointing to null Node
 *
 * x => pointer to the SingleLinkedList
 * return pointer to the iterator
 */
void SLinkedListGetIterator(SlinkedList *x, SIterator *y);    //O(1)

/** 
 * Function: SLinkedListIteratorGetCurrent
 * ---------------
 * write the current node's data to the target address
 *
 * Iterator => pointer to the Iterator
 * it will write the current node's data to the targetAddress
 */
void SLinkedListIteratorGetCurrent(void *Iterator, void *targetAddress);    //O(1)

/** 
 * Function: SLinkedListIteratorHasNext
 * ---------------
 * check if there is next node 
 *
 * Iterator => pointer to the Iterator
 * it will return 1 if there is node, 0 otherwise
 */
int SLinkedListIteratorHasNext(void *Iterator);    //O(1)

/** 
 * Function: SLinkedListIteratorGetNext
 * ---------------
 * write the current next node's data to the target address
 *
 * Iterator => pointer to the Iterator
 * it will write the next node's data to the targetAddress
 */
void SLinkedListIteratorGetNext(void *Iterator, void *targetAddress);    //O(1)

/** 
 * Function: SLinkedListIteratorGoNext
 * ---------------
 * advance the Iterator to the forward
 *
 * Iterator => pointer to the Iterator
 * it will make the iterator point to the next node
 */
void SLinkedListIteratorGoNext(void *Iterator);    //O(1)

#endif