/** 
 * File: ChainHash.h
 * ---------------
 * Defines the interface for the hash map.
 *
 * This version of the hash map allow the client to add generic item
 * to a Tree and do other operation in O(1) in average.
 */
#ifndef _CHAINHASH_
#define _CHAINHASH_

/** 
 * Type: _HashmapChain_state
 * ---------------
 * state of the operation
 */
typedef enum {
    _HashmapChain_SUCC, _HashmapChain_MEMERR, _HashmapChain_SIZEERR
} _HashmapChain_state;

/** 
 * Type: FreeFunction
 * ---------------
 * Defines the Function needed to free the  elements when needed
 *
 * FreeFunction is pointer to client-supplied function to free the items
 * When dispose the Hash map or when element need to be freed. the function will
 * recieve one element at time and it's job to free it. client will need to use it 
 * with all malloced variable, client will send NULL if it's in the stack
 */
typedef void (*FreeFunction)(void *);

/** 
 * Type: CompareFunction
 * ---------------
 * Defines the Function needed to compare two elements in the map
 *
 * Takes two pointers to the start of two element and should compare them and 
 * return the result
 * MUST return one IF P1 == P2, zero otherwise
 */
typedef int (*CompareFunction)(void *, void *);

/** 
 * Type: Hash
 * ---------------
 * Defines the Function needed to hash any element in the map
 *
 * Takes pointer to the key of the element and it's size and max hashed number
 * should return valid hash number
 */
typedef unsigned int (*Hash)(void *key, int keysize, long long max);


//memory abs
typedef void *(*mallocDatax)(size_t);

typedef void (*freeDatax)(void *);


/** 
 * Type: HashmapChain
 * ---------------
 * Defines the Struct needed for the Hash map
 *
 * size => number of the element in the hash map
 * elemsize => the size in Byte for each element in the map
 * data => pointer to the array of linkedlist
 * datafreeFN => pointer to client supplied function used when freeing the data element
 * keyfreeFN => pointer to client supplied function used when freeing the key element
 * CmpFN => pointer to client supplied function used when comparing the key elements
 */
typedef struct HashmapChain {
    long long size;
    long long actualsize;
    int elemsize;
    int keysize;
    SlinkedList **data;
    FreeFunction datafreeFN;
    FreeFunction keyfreeFN;
    CompareFunction CmpFN;
    Hash getHash;
    mallocData MD;
    freeData FD;
} HashmapChain;

/** 
 * Type: DataKey
 * ---------------
 * Defines the Struct needed for the DataKey
 *
 * data => pointing to the data
 * key => pointing to the key
 */
typedef struct DataKey {
    void *data;
    void *key;
} DataKey;

/** 
 * Function: InitializeHashmapChain
 * ---------------
 * Initialize the given HashmapChain
 *
 * x => pointer to the Hashmap
 * datafreeFN => pointer to client supplied function used when freeing the data element
 * keyfreeFN => pointer to client supplied function used when freeing the key element
 * CmpFN => pointer to client supplied function used when comparing the key elements
 */
_HashmapChain_state InitializeHashmapChain(HashmapChain *x, int dataSize, int keySize, CompareFunction,
                                           FreeFunction datafreeFN, FreeFunction keyfreeFN, Hash hashFn, mallocData MD,
                                           freeData FD);

/** 
 * Function: DisposeHashmapChain
 * ---------------
 * Dispose the given HashmapChain
 *
 * x => pointer to the Hashmap
 */
_HashmapChain_state DisposeHashmapChain(HashmapChain *x);

/** 
 * Function: HashmapChainAddKey
 * ---------------
 * Add element with key the given HashmapChain
 *
 * x => pointer to the Hashmap
 * key => pointer to the key that related to the element
 * elementAddress => pointer to the element you want to store
 */
_HashmapChain_state HashmapChainAddKey(HashmapChain *x, void *key, void *elementAddress);

/** 
 * Function: HashmapChainSearch
 * ---------------
 * search for element with key in the given HashmapChain
 *
 * x => pointer to the Hashmap
 * key => pointer to the key you want to search for
 * targetAddress => pointer to the part of memory you want to write the
 * element data into if it found
 * found = 1 if the key was found and written to tragetAddress, 0
 * otherwise
 */
_HashmapChain_state HashmapChainSearch(HashmapChain *x, void *key, void *targetAddress, int *found);

/** 
 * Function: HashmapChainDelete
 * ---------------
 * search for element with key in the given HashmapChain
 *
 * x => pointer to the Hashmap
 * key => pointer to the key you want to delete the element related with
 * userDel = 1 then the function will use the user defined function to free the element.
 * return 1 if the key was found and deleted, 0 otherwise
 */
_HashmapChain_state HashmapChainDelete(HashmapChain *x, void *key, int *found, int userDel);

/**
 * Function: HashmapChainSize
 * ---------------
 * return number of items in the hashmap.
 *
 * x => pointer to the Hashmap
 */
long long HashmapChainSize(HashmapChain *x);

#endif
