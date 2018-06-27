//Language Libraries
#include "singly_linked_list.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

//create and return Node in the heap
static inline SinglyLinkedListNode *create_node(SinglyLinkedList *list, void *element_address, SinglyLinkedListNode *next) {

    //malloc the node
    SinglyLinkedListNode *element = (SinglyLinkedListNode *) list->malloc(sizeof(SinglyLinkedListNode));
    if (!element){
        return NULL;
    }

    //malloc space for the data in the node
    element->element = (void *) list->malloc(list->element_size);
    if (!element->element){
        return NULL;
    }

    //write the data in the Node
    memcpy(element->element, element_address, list->element_size);

    //set the node next
    element->next = next;

    //return the node
    return element;
}

//free the node and it's data
static inline void totally_free_node(SinglyLinkedList *list, SinglyLinkedListNode *node) {

    //if the user supply function use it, else just free the node
    if (list->element_free_function != NULL) {
        list->element_free_function(node->element);
    }

    list->free(node->element);
    list->free(node);

}

//free the node and it's data
static inline void free_node_with_no_user_element_free_function(SinglyLinkedList *list, SinglyLinkedListNode *node) {
    //Don't use the user supplied function
    list->free(node->element);
    list->free(node);
}

//free the node and it's data
static inline void free_dummy_node(SinglyLinkedList *list, SinglyLinkedListNode *node) {
    list->free(node);
}

SinglyLinkedListState initialize_singly_linked_list(SinglyLinkedList *list, uint32_t element_size,
                                                    ElementsFreeFunction element_free_function, MallocFunction malloc,
                                                    FreeFunction free) {
    //initialize the linkedList
    list->element_size = element_size;
    list->element_free_function = element_free_function;
    list->size = 1;
    list->free = free;
    list->malloc = malloc;

    //make dummy node at the head
    SinglyLinkedListNode *first = (SinglyLinkedListNode *) list->malloc(sizeof(SinglyLinkedListNode));
    if (!first){
        //handle memory error
        return singly_linked_list_memory_error;
    }

    //set data to the node
    first->next = NULL;
    first->element = NULL;

    //make the head and the end point to the sentail node
    list->head = first;
    list->end = first;

    //succeeded
    return singly_linked_list_succeed;
}

SinglyLinkedListState dispose_singly_linked_list(SinglyLinkedList *list) {

    //free first empty node and set the pointers to the first actual node
    SinglyLinkedListNode *first_iterator = list->head;
    SinglyLinkedListNode *second_iterator = first_iterator->next;
    free_dummy_node(list, first_iterator);
    first_iterator = second_iterator;

    //Free every Node
    for (uint64_t i = 0; i < singly_linked_list_size(list); i++) {
        second_iterator = first_iterator->next;
        totally_free_node(list, first_iterator);
        first_iterator = second_iterator;
    }

    //succeeded
    return singly_linked_list_succeed;
}

uint64_t singly_linked_list_size(SinglyLinkedList *list) {
    return list->size - 1;
}

SinglyLinkedListState singly_linked_list_add_front(SinglyLinkedList *list, void *element_address) {

    SinglyLinkedListNode *first_node = list->head;

    //create Node pointing to the first node
    SinglyLinkedListNode *element = create_node(list, element_address, first_node->next);
    if (!element){
        //handle memory error
        return singly_linked_list_memory_error;
    }

    //if it's the first element, make the end point to it
    if (singly_linked_list_size(list) == 0) {
        list->end = element;
    }

    //fix the head node and increase the size
    first_node->next = element;
    list->size++;

    //succeeded
    return singly_linked_list_succeed;
}

SinglyLinkedListState singly_linked_list_remove_front(SinglyLinkedList *list) {
    
    //if there is no data just return with error.
    if (singly_linked_list_size(list) == 0){
        return singly_linked_list_size_error;
    }
    
    //fix the end pointer
    if (singly_linked_list_size(list) == 1) {
        list->end = list->head;
    }
    
    //else free the node and fix the pointers and decrease the size.
    SinglyLinkedListNode *temp = list->head->next->next;
    totally_free_node(list, list->head->next);
    list->head->next = temp;
    list->size--;

    return singly_linked_list_succeed;    //succeeded
}

SinglyLinkedListState singly_linked_list_removeFrontOnly(SinglyLinkedList *list) {

    //if there is no data just return with an error
    if (singly_linked_list_size(list) == 0){
        return singly_linked_list_size_error;
    }

    //fix the end pointer
    if (singly_linked_list_size(list) == 1) {
        list->end = list->head;
    }

    //else free the node and fix the pointers and decrease the size
    SinglyLinkedListNode *temp = list->head->next->next;
    free_node_with_no_user_element_free_function(list, list->head->next); /* difference */
    list->head->next = temp;
    list->size--;

    return singly_linked_list_succeed;    //succeeded
}

SinglyLinkedListState singly_linked_list_peek_front(SinglyLinkedList *list, void *target_address) {

    //if there is no data just return with an error
    if (singly_linked_list_size(list) == 0){
        return singly_linked_list_size_error;
    }

    //copy the data to pointer
    memcpy(target_address, list->head->next->element, list->element_size);

    return singly_linked_list_succeed;    //succeeded
}

SinglyLinkedListState singly_linked_list_extract_front(SinglyLinkedList *list, void *target_address) {
    //write the data then remove it
    singly_linked_list_peek_front(list, target_address);
    return singly_linked_list_remove_front(list);
}

SinglyLinkedListState singly_linked_list_add_back(SinglyLinkedList *list, void *element_address) {

    SinglyLinkedListNode *last_node = list->end;

    //create new node pointing to the end
    SinglyLinkedListNode *element = create_node(list, element_address, NULL);
    if (!element){
        return singly_linked_list_memory_error;
    }

    //fix the end pointer and increase the size
    last_node->next = element;
    list->end = element;
    list->size++;

    return singly_linked_list_succeed;     //succeeded
}

SinglyLinkedListState singly_linked_list_remove_back(SinglyLinkedList *list) {
    
    //if there is no nodes just return
    if (singly_linked_list_size(list) == 0){
        return singly_linked_list_size_error;
    }
    
    //else get to the wanted node
    SinglyLinkedListNode *current = list->head;
    while (current->next != list->end) {
        current = current->next;
    }
    
    //free it and fix the end pointer
    totally_free_node(list, current->next);
    current->next = NULL;
    list->end = current;
    list->size--;

    return singly_linked_list_succeed;    //succeeded
}

SinglyLinkedListState singly_linked_list_removeBackOnly(SinglyLinkedList *list) {

    //if there is no nodes just return an error
    if (singly_linked_list_size(list) == 0){
        return singly_linked_list_size_error;
    }

    //else get to the wanted node
    SinglyLinkedListNode *current = list->head;
    while (current->next != list->end) {
        current = current->next;
    }

    //free it and fix the end pointer
    free_node_with_no_user_element_free_function(list, current->next);
    current->next = NULL;
    list->end = current;
    list->size--;

    return singly_linked_list_succeed;    //succeeded
}

SinglyLinkedListState singly_linked_list_peek_back(SinglyLinkedList *list, void *target_address) {

    //if there is no data just return
    if (singly_linked_list_size(list) == 0){
        return singly_linked_list_size_error;
    }

    //write the data to the address given
    memcpy(target_address, list->end->element, list->element_size);

    return singly_linked_list_succeed;    //succeeded
}

SinglyLinkedListState singly_linked_list_extract_back(SinglyLinkedList *list, void *target_address) {
    //write the data then remove the data
    singly_linked_list_peek_back(list, target_address);
    return singly_linked_list_remove_back(list);
}

SinglyLinkedListState singly_linked_list_get(SinglyLinkedList *list, uint32_t index, void *target_address) {

    //if the index bigger than or equal the list, return
    if (index >= singly_linked_list_size(list)) {
        return singly_linked_list_size_error;
    }

    //else go to the node wanted
    SinglyLinkedListNode *current = list->head;
    for (uint64_t i = 0; i < index; i++) {
        current = current->next;
    }

    //write the data to target_address
    memcpy(target_address, current->next->element, list->element_size);

    return singly_linked_list_succeed;    //succeeded
}

SinglyLinkedListState singly_linked_list_remove(SinglyLinkedList *list, uint32_t index) {

    //if the index bigger than or equal the list, return with an error
    if (index >= singly_linked_list_size(list)){
        return singly_linked_list_size_error;
    }

    //fix the start and end pointers
    if (index == 0) {
        return singly_linked_list_remove_front(list);
    } else if (index == singly_linked_list_size(list) - 1) {
        return singly_linked_list_remove_back(list);
    }

    //else go to the node wanted
    SinglyLinkedListNode *current = list->head;
    for (uint64_t i = 0; i < index; i++) {
        current = current->next;
    }

    //Free the node and fix the pointers and decrease the size
    totally_free_node(list, current->next);
    current->next = current->next->next;
    list->size--;

    return singly_linked_list_succeed;    //succeeded
}

SinglyLinkedListState singly_linked_list_insert(SinglyLinkedList *list, uint32_t index, void *element_address) {

    //if the index bigger than the list, return
    if (index > singly_linked_list_size(list)){
        return singly_linked_list_size_error;
    }

    if (index == 0) {

        /* if the index is zero, insert it in the front */
        return singly_linked_list_add_front(list, element_address);

    } else if (index == singly_linked_list_size(list)) {

        /* if the index is list size, insert it in the back */
        return singly_linked_list_add_back(list, element_address);

    } else {

        /* if the index is in between, get the node and create the node and increase the size */
        SinglyLinkedListNode *current = list->head;
        for (uint64_t i = 0; i < index; i++) {
            current = current->next;
        }

        SinglyLinkedListNode *new_node = create_node(list, element_address, current->next);
        if (!new_node){
            return singly_linked_list_memory_error;
        }

        current->next = new_node;
        list->size++;
    }
    return singly_linked_list_succeed;    //succeeded
}

SinglyLinkedListState singly_linked_list_search(SinglyLinkedList *list, void *key_address,
                                                ElementsCompareFunction compare_function, int32_t *index) {

    //search the linked list for key, using the ElementsCompareFunction provided by the user
    //return first index of the key if found else -1
    SinglyLinkedListNode *current = list->head;

    for (uint64_t i = 0; i < singly_linked_list_size(list); i++) {

        current = current->next;

        if (compare_function(key_address, current->element)) {
            *index = i;
            return singly_linked_list_succeed;    //found
        }

    }

    *index = -1;
    return singly_linked_list_succeed;    //not found
}

void singly_linked_list_get_iterator(SinglyLinkedList *list, SinglyLinkedListIterator *iterator) {
    iterator->node = list->head;
    iterator->list = list;
}

void singly_linked_list_iterator_get_current(SinglyLinkedListIterator *iterator, void *target_address) {
    memcpy(target_address, iterator->node->element, iterator->list->element_size);
}

int singly_linked_list_iterator_has_next(SinglyLinkedListIterator *iterator) {
    return iterator->node->next != NULL;
}

void singly_linked_list_iterator_get_next(SinglyLinkedListIterator *iterator, void *target_address) {
    //cast and get the next element's data
    memcpy(target_address, iterator->node->next->element, iterator->list->element_size);
}

void singly_linked_list_iterator_go_next(SinglyLinkedListIterator *iterator) {
    iterator->node = iterator->node->next;
}