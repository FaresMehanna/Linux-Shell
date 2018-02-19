//create and return Node in the heap
static inline Snode* CreateNode(SlinkedList* x, void* elementAddress, Snode* next){
	//malloc the node
	Snode* element = (Snode *) x->MD(sizeof(Snode));
	if(!element)	return NULL;
	//malloc space foe the data in the node
	element->element = (void *) x->MD(x->elemsize);
	if(!element->element)	return NULL;
	//write the data in the Node
	memcpy(element->element, elementAddress, x->elemsize);
	//set the node next
	element->next = next;
	//return the node
	return element;
}

//free the node and it's data
static inline void FreeNode(SlinkedList* x, Snode* node){
	//if the user supply function use it, else just free the node
	if(x->freeFN != NULL)
		x->freeFN(node->element);
	x->FD(node->element);
	x->FD(node);
}

//free the node and it's data
static inline void FreeNodeOnly(SlinkedList* x, Snode* node){
	//Don't use the user supplied function
	x->FD(node->element);
	x->FD(node);
}

//free the node and it's data
static inline void OFreeNode(SlinkedList* x, Snode* node){
	x->FD(node);
}

static inline _SlinkedList_state InitializeSLinkedList(SlinkedList* x, int elementSize, FreeFunction freeFN,
	mallocData MD, freeData FD){
	//initialize the linkedlist
	x->elemsize = elementSize;
	x->freeFN = freeFN;
	x->size = 1;
	x->MD = MD;
	x->FD = FD;
	//make sential node at the head
	Snode* first = (Snode *)x->MD(sizeof(Snode));
	if(!first)	return _SlinkedList_MEMERR;	//handle memory error
	first->next =  NULL;
	first->element =  NULL;
	//make the head and the end point to the sentail node
	x->head = first;
	x->end = first;
	//return SUCC
	return _SlinkedList_SUCC;
}

static inline _SlinkedList_state DisposeSLinkedList(SlinkedList* x){
	//free first empty node and set the pointers to the first actual node
	Snode* It = x->head;
	Snode* nex = It->next;
	OFreeNode(x,It);
	It = nex;
	//Free every Node
	for(int i=0;i<SLinkedListSize(x);i++){
		nex = It->next;
		FreeNode(x,It);
		It = nex;
	}
	return _SlinkedList_SUCC;	//return SUCC
}

static inline long long SLinkedListSize(SlinkedList* x){
	return x->size-1;
}

static inline _SlinkedList_state SLinkedListAddFront(SlinkedList* x,void* elementAddress){
	Snode* firstNode = x->head;
	//create Node pointing to the first node
	Snode* element = CreateNode(x,elementAddress,firstNode->next);
	if(!element)	return _SlinkedList_MEMERR;	//handle memory error
	//if it's the first element, make the end point to it
	if(SLinkedListSize(x) == 0)
		x->end = element;
	//fix the head node and increase the size
	firstNode->next = element;
	x->size++;
	return _SlinkedList_SUCC;	//return SUCC
}

static inline _SlinkedList_state SLinkedListRemoveFront(SlinkedList* x){
	//if there is no data just return
	if(SLinkedListSize(x) == 0)	return _SlinkedList_SIZEERR;
	//fix the end pointer
	if(SLinkedListSize(x) == 1)
		x->end = x->head;
	//else free the node and fix the pointers and decrease the size
	Snode* temp = x->head->next->next;
	FreeNode(x,x->head->next);
	x->head->next = temp;
	x->size--;
	return _SlinkedList_SUCC;	//return SUCC
}

static inline _SlinkedList_state SLinkedListRemoveFrontOnly(SlinkedList* x){
	//if there is no data just return
	if(SLinkedListSize(x) == 0)	return _SlinkedList_SIZEERR;
	//fix the end pointer
	if(SLinkedListSize(x) == 1)
		x->end = x->head;
	//else free the node and fix the pointers and decrease the size
	Snode* temp = x->head->next->next;
	FreeNodeOnly(x,x->head->next);
	x->head->next = temp;
	x->size--;
	return _SlinkedList_SUCC;	//return SUCC
}

static inline _SlinkedList_state SLinkedListPeekFront(SlinkedList* x, void* targetAddress){
	//if there is no data just return
	if(SLinkedListSize(x) == 0)	return _SlinkedList_SIZEERR;
	//copy the data to pointer
	memcpy(targetAddress,x->head->next->element,x->elemsize);
	return _SlinkedList_SUCC;	//return SUCC
}

static inline _SlinkedList_state SLinkedListExtractFront(SlinkedList* x, void* targetAddress){
	//write the data then remove it
	SLinkedListPeekFront(x,targetAddress);
	return SLinkedListRemoveFront(x);
}

static inline _SlinkedList_state SLinkedListAddBack(SlinkedList* x, void* elementAddress){
	Snode* lastNode = x->end;
	//create new node pointing to the end
	Snode* element = CreateNode(x,elementAddress,NULL);
	if(!element)	return _SlinkedList_MEMERR;
	//fix the end pointer and increase the size
	lastNode->next = element;
	x->end = element;
	x->size++;
	return _SlinkedList_SUCC;	 //return SUCC
}

static inline _SlinkedList_state SLinkedListRemoveBack(SlinkedList* x){
	//if there is no nodes just return
	if(SLinkedListSize(x) == 0)	return _SlinkedList_SIZEERR;
	//else get to the wanted node
	Snode* curr = x->head;
	while(curr->next != x->end){
		curr = curr->next;
	}
	//free it and fix the end pointer
	FreeNode(x,curr->next);
	curr->next = NULL;
	x->end = curr;
	x->size--;
	return _SlinkedList_SUCC;	//return SUCC
}

static inline _SlinkedList_state SLinkedListRemoveBackOnly(SlinkedList* x){
	//if there is no nodes just return
	if(SLinkedListSize(x) == 0)	return _SlinkedList_SIZEERR;
	//else get to the wanted node
	Snode* curr = x->head;
	while(curr->next != x->end){
		curr = curr->next;
	}
	//free it and fix the end pointer
	FreeNodeOnly(x,curr->next);
	curr->next = NULL;
	x->end = curr;
	x->size--;
	return _SlinkedList_SUCC;	//return SUCC
}

static inline _SlinkedList_state SLinkedListPeekBack(SlinkedList* x, void* targetAddress){
	//if there is no data just return
	if(SLinkedListSize(x) == 0)	return _SlinkedList_SIZEERR;
	//write the data to the address given
	memcpy(targetAddress,x->end->element,x->elemsize);
	return _SlinkedList_SUCC;	//return SUCC
}

static inline _SlinkedList_state SLinkedListExtractBack(SlinkedList* x, void* targetAddress){
	//write the data then rmeove the data
	SLinkedListPeekBack(x,targetAddress);
	return SLinkedListRemoveBack(x);
}

static inline _SlinkedList_state SLinkedListGet(SlinkedList* x, int index, void* targetAddress){
	//if the index bigger than or equal the list, return
	if(index >= SLinkedListSize(x) || index < 0)	return _SlinkedList_SIZEERR;
	//else go to the node wanted
	Snode* curr = x->head;
	for(int i=0;i<index;i++){
		curr = curr->next;
	}
	//write the data to targetAddress
	memcpy(targetAddress,curr->next->element,x->elemsize);
	return _SlinkedList_SUCC;	//return SUCC
}

static inline _SlinkedList_state SLinkedListRemove(SlinkedList* x, int index){
	//if the index bigger than or equal the list, return
	if(index >= SLinkedListSize(x) || index < 0)	return _SlinkedList_SIZEERR;
	//fix the start and end pointers
	if(index == 0)
		return SLinkedListRemoveFront(x);
	else if(index == SLinkedListSize(x)-1)
		return SLinkedListRemoveBack(x);
	//else go to the node wanted
	Snode* curr = x->head;
	for(int i=0;i<index;i++){
		curr = curr->next;
	}
	//Free the node and fix the pointers and decrease the size
	FreeNode(x,curr->next);
	curr->next = curr->next->next;
	x->size--;
	return _SlinkedList_SUCC;	//return SUCC
}

static inline _SlinkedList_state SLinkedListInsert(SlinkedList* x, int index, void* elementAddress){
	//if the index bigger than the list, return
	if(index > SLinkedListSize(x) || index < 0)	return _SlinkedList_SIZEERR;
	//if the index is zero, insert it in the front
	else if(index == 0)
		return SLinkedListAddFront(x,elementAddress);
	//if the index is Listsize, insert it in the back
	else if(index == SLinkedListSize(x))
		return SLinkedListAddBack(x,elementAddress);
	//if the index is in between, get the node and create the node and increase the size
	else{
		Snode* curr = x->head;
		for(int i=0;i<index;i++){
			curr = curr->next;
		}
		Snode* newNode = CreateNode(x,elementAddress,curr->next);
		if(!newNode)	return _SlinkedList_MEMERR;
		curr->next = newNode;
		x->size++;
	}
	return _SlinkedList_SUCC;	//return SUCC
}

static inline _SlinkedList_state SLinkedListSearch(SlinkedList* x, void* keyAddress, CompareFunction cmpFN, int* index){
	//search the linked list for key, using the CompareFunction provided by the user
	//return first index of the key if found else -1
	Snode* curr = x->head;
	for(int i=0;i<SLinkedListSize(x);i++){
		curr = curr->next;
		if(cmpFN(keyAddress,curr->element)){
			*index = i;
			break;
		}
	}
	*index = -1;
	return _SlinkedList_SUCC;	//return SUCC
}

static inline void SLinkedListGetIterator(SlinkedList* x, SIterator* y){
	y->node = x->head;
	y->list = x;
}

static inline void SLinkedListIteratorGetCurrent(void* Iterator, void* targetAddress){
	//cast and get the current element's data
	SIterator* y = (SIterator *) Iterator;
	memcpy(targetAddress,y->node->element,y->list->elemsize);
}

static inline int SLinkedListIteratorHasNext(void* Iterator){
	//cast and chech if it has next node
	SIterator* y = (SIterator *) Iterator;
	return  y->node->next != NULL;
}

static inline void SLinkedListIteratorGetNext(void* Iterator, void* targetAddress){
	//cast and get the next element's data
	SIterator* y = (SIterator *) Iterator;
	memcpy(targetAddress,y->node->next->element,y->list->elemsize);
}

static inline void SLinkedListIteratorGoNext(void* Iterator){
	//cast and move the pointer to the next node
	SIterator* y = (SIterator *) Iterator;
	y->node = y->node->next;
}

static inline char* stateToMsg(_SlinkedList_state state){
	char* error = malloc(sizeof(char)*64);
	if(!error)	return NULL;
	switch(state){
		case _SlinkedList_SUCC:
			error = "No errors, Everything is OK";
		break;
		case _SlinkedList_SIZEERR:
			error = "Size Error, your LinkedList is probably empty.";
		break;
		case _SlinkedList_MEMERR:
			error = "Memory Error, can't mallocate more data.";
		break;
	}
	return error;
}