//Language Libraries
#include <stdlib.h>
#include <stdint.h>

//Data Structures Libraries
#include "../../datastructures/singly_linked_list/singly_linked_list.h"

//Modules Libraries
#include "memory_manager.h"

//function to get hash value for the addresses
static inline uint64_t generate_hash(void *key, int keysize, long long max) {
    return (*(uint64_t *) key) % max;
}

//function to compare addresses for hash map
static int compare_uint64_t(void *p1, void *p2) {
    return *(uint64_t *) p1 == *(uint64_t *) p2;
}

//function to free addresses
static inline void free_hash(void *p1) {
    free(*(void **) p1);
}

static inline void initialize_memory_map() {

    //malloc size of the list.
    Global_Memory_Storage.map = malloc(sizeof(SinglyLinkedList));

    if (!Global_Memory_Storage.map) {
        exit(50);
    }

    //initialize the list with the wanted parameters.
    initialize_singly_linked_list(Global_Memory_Storage.map,
                           sizeof(uint64_t), NULL, malloc, free);
}

void *smalloc(size_t size) {

    //if no hash map initialize it
    if (Global_Memory_Storage.map == NULL) {
        initialize_memory_map();
    }

    //malloc the wanted size
    void *address = malloc(size);
    uint64_t x = (uint64_t) address;

    //add the address to the hash map
    if (address != NULL) {
        singly_linked_list_add_front(Global_Memory_Storage.map, &x);
   }

    //return the address
    return address;
}

void sfree(void *ptr) {

    uint64_t address = (uint64_t) ptr;

    //delete the address from the list if found and free the data
    int32_t index;
    singly_linked_list_search(Global_Memory_Storage.map, &address, compare_uint64_t, &index);

    if (index != -1) {
        singly_linked_list_remove(Global_Memory_Storage.map, index);
    }
}

void *srealloc(void *ptr, uint64_t newSize){

    //if no ptr==NULL then use smalloc
    if (!ptr) {
        return smalloc(newSize);
    }

    //re alloc new data
    void *address = realloc(ptr, newSize);
    uint64_t x = (uint64_t) address;
    uint64_t y = (uint64_t) ptr;

    int found;
    //if the reallocation succeeded and return different value, remove the old
    //without freeing it and add new one
    if (address != NULL && x != y) {

        int32_t index;
        //Delete the data from the list
        singly_linked_list_search(Global_Memory_Storage.map, &y, compare_uint64_t, &index);
        if (index != -1) {
            singly_linked_list_remove(Global_Memory_Storage.map, index);
        }

        //add to the list
        singly_linked_list_add_front(Global_Memory_Storage.map, &x);
    }

    return address;
}

void memory_clear() {

    if (Global_Memory_Storage.map == NULL) {
        return;
    }

    //remove the list with all it's keys
    dispose_singly_linked_list(Global_Memory_Storage.map);

    //free the map itself
    free(Global_Memory_Storage.map);
    Global_Memory_Storage.map = NULL;    //protect the map
}