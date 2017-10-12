#include "ChainHash.h"

static inline unsigned int getHash(void* key, int keysize, long long max){
	unsigned int hash = 2166136261;
	for(int i=0;i<keysize;i++){
		hash = hash ^ (*(char *)key + i);
 		hash = hash * 16777619;
 	}
	return hash % max;
}

static inline DataKey* createDataKey(HashmapChain* x ,void* key ,void* elementAddress){
	//create the pair
	DataKey* y = x->MD(sizeof(DataKey));
	if(!y)	return NULL;
	y->data = x->MD(x->elemsize);
	if(!y->data)	return NULL;
	y->key = x->MD(x->keysize);
	if(!y->key)	return NULL;
	//map the data
	memcpy (y->data,elementAddress,x->elemsize);
	memcpy (y->key,key,x->keysize);
	//return
	return y;
}

static inline void userDeleteDataKeyPair(HashmapChain* x ,DataKey* y, int keyData){
	if(keyData){
		if(x->datafreeFN != NULL)
			x->datafreeFN(y->data);
		if(x->keyfreeFN != NULL)
			x->keyfreeFN(y->key);
	}

	x->FD(y->key);
	x->FD(y->data);	
	x->FD(y);
}

static inline void totalyDeleteLinkedList(HashmapChain* x ,SlinkedList* l){
	DataKey* y;
	SIterator it;
	void* iterator = &it;
	SLinkedListGetIterator(l,iterator);
	while(SLinkedListIteratorHasNext(iterator)){
		//get the item
		SLinkedListIteratorGetNext(iterator,&y);
		SLinkedListIteratorGoNext(iterator);
		//delete the item
		userDeleteDataKeyPair(x,y,1);
	}
	//free the linkedlist
	DisposeSLinkedList(l);
}

static inline int getIndexFromLinkedList(HashmapChain* x,SlinkedList* SL, void* key, int* targetAddressForIndex){
	//create datakey pair
	DataKey* y;
	//get the index from the list
	SIterator it;
	void* iterator = &it;
	SLinkedListGetIterator(SL,iterator);
	int index = 0;
	int found = 0;
	while(SLinkedListIteratorHasNext(iterator)){
		//get the item
		SLinkedListIteratorGetNext(iterator,&y);
		SLinkedListIteratorGoNext(iterator);
		//is it the one we wanted ?
		if(x->CmpFN(y->key,key)){
			found = 1;
			break;
		}
		index++;
	}
	if(found)
		*targetAddressForIndex = index;
	return found;
}

static inline _HashmapChain_state GrowHashmapChain(HashmapChain* x){
	int factor = 4;
	int factorSize = 2;
	//if the sizes aren't the same return
	if(x->actualsize != factor*x->size)
		return _HashmapChain_SUCC;
	//pointer to the old array of pointers
	SlinkedList** old = x->data;
	SlinkedList** newH = x->MD(sizeof(SlinkedList*) * x->actualsize * factor * 2 * factorSize);
	//make the new array of pointers
	if(!newH)	return _HashmapChain_MEMERR;
	//create the lists for the new array
	for(int i=0;i<x->actualsize*factor*2*factorSize;i++){
		(newH)[i] = x->MD(sizeof(SlinkedList));
		if(!newH[i])	return _HashmapChain_MEMERR;
		if(InitializeSLinkedList(newH[i],sizeof(DataKey*),NULL,x->MD,x->FD) != _SlinkedList_SUCC)
			return _HashmapChain_MEMERR;
	}
	//delete the old array and create new one
	DataKey* y;
	for(int i=0;i<x->actualsize;i++){
		//current linkedList
		SlinkedList* curr = old[i];
		//Iterator to it
		SIterator it;
		void* iterator = &it;
		SLinkedListGetIterator(curr,iterator);
		//iterate through the linkedlist
		while(SLinkedListIteratorHasNext(iterator)){
			//get the item
			SLinkedListIteratorGetNext(iterator,&y);
			SLinkedListIteratorGoNext(iterator);
			//new hash
			unsigned int hash = x->getHash(y->key,x->keysize, x->actualsize);	
			//add to the new list
			if(SLinkedListAddFront(newH[hash], &y) != _SlinkedList_SUCC)
				return _HashmapChain_MEMERR;
		}
		//free the linkedlist
		DisposeSLinkedList(curr);
		//free the linkedlist itself
		x->FD(curr);
	}
	x->data = newH;
	x->actualsize = x->actualsize * factor * 2 * factorSize;
	//free the old array
	x->FD(old);
	return _HashmapChain_SUCC;	//return SUCC
}

static inline _HashmapChain_state InitializeHashmapChain(HashmapChain* x, int dataSize, int keySize, CompareFunction CmpFN,
 FreeFunction datafreeFN, FreeFunction keyfreeFN, Hash hashFn, mallocDatax MD, freeDatax FD){
	//initialize the data in the tree
	x->size = 0;
	x->actualsize = 8;
	x->elemsize = dataSize;
	x->keysize = keySize;
	x->MD = MD;
	x->FD = FD;
	//the array holding the pointers to the linkedlists
	x->data = x->MD(sizeof(SlinkedList*) * 8);
	if(!(x->data))	return _HashmapChain_MEMERR;
	//malloc the LinkedLists
	for(int i=0;i<8;i++){
		(x->data)[i] = x->MD(sizeof(SlinkedList));
		if(!(x->data)[i])	return _HashmapChain_MEMERR;
		if(InitializeSLinkedList((x->data)[i],sizeof(DataKey*),NULL,x->MD,x->FD) != _SlinkedList_SUCC)
			return _HashmapChain_MEMERR;
	}
	x->datafreeFN = datafreeFN;
	x->keyfreeFN = keyfreeFN;
	x->CmpFN = CmpFN;
	x->getHash = getHash;
	if(hashFn != NULL)
		x->getHash = hashFn;
	return _HashmapChain_SUCC;	//return SUCC
}

static inline _HashmapChain_state DisposeHashmapChain(HashmapChain* x){
	//the array of linkedlists
	SlinkedList** temp = x->data;
	for(int i=0;i<x->actualsize;i++){
		//the current linkedlist
		SlinkedList* curr = temp[i];
		//delete the data
		totalyDeleteLinkedList(x,curr);
		//free the linkedlist
		x->FD((x->data)[i]);
	}
	//free the array of pointers
	x->FD(temp);
	return _HashmapChain_SUCC;	//return SUCC
}


static inline _HashmapChain_state HashmapChainAddKey(HashmapChain* x, void* key, void* elementAddress){
	//grow the map if needed
	GrowHashmapChain(x);
	//get the hash value
	unsigned int hash = x->getHash(key,x->keysize,x->actualsize);
	//create datakey pair
	DataKey* y = createDataKey(x,key,elementAddress);
	if(!y)	return _HashmapChain_MEMERR;
	int index = 0;
	if(getIndexFromLinkedList(x,(x->data)[hash],key,&index)){
		//get the current key
		DataKey* temp;
		SLinkedListGet((x->data)[hash], index, &temp);
		//delete it by the user defined functions
		userDeleteDataKeyPair(x,temp,1);
		//remove it from the list
		SLinkedListRemove((x->data)[hash], index);
		//add the new one
		if(SLinkedListAddFront((x->data)[hash], &y) != _SlinkedList_SUCC)
			return _HashmapChain_MEMERR;
	}else{
		//printf("%lld \n",SLinkedListSize((x->data)[hash]));
		if(SLinkedListAddFront((x->data)[hash], &y) != _SlinkedList_SUCC)
			return _HashmapChain_MEMERR;
		//increase the size
		x->size++;
	}
	return _HashmapChain_SUCC;
}


static inline _HashmapChain_state HashmapChainSearch(HashmapChain* x, void* key, void* targetAddress, int* found){
	//get the hash value
	unsigned int hash = x->getHash(key,x->keysize,x->actualsize);
	//create datakey pair
	DataKey* y;
	int index;
	if(getIndexFromLinkedList(x,(x->data)[hash],key,&index)){
		SLinkedListGet((x->data)[hash], index, &y);
		memcpy(targetAddress,y->data,x->elemsize);
		*found = 1;
	}
	*found = 0;
	return _HashmapChain_SUCC;
}

static inline _HashmapChain_state HashmapChainDelete(HashmapChain* x, void* key, int* found, int userDel){
	//get the hash value
	unsigned int hash = x->getHash(key,x->keysize,x->actualsize);
	//create datakey pair
	DataKey* y;
	//get the index from the list
	int index;
	if(getIndexFromLinkedList(x,(x->data)[hash],key,&index)){
		//get the pair
		SLinkedListGet((x->data)[hash], index, &y);
		//user delete it
		userDeleteDataKeyPair(x,y,userDel);
		//linkedlist delete it
		SLinkedListRemove((x->data)[hash], index);
		*found = 1;
	}
	*found = 0;
	return _HashmapChain_SUCC;
}

static inline long long HashmapChainSize(HashmapChain* x){
	return x->size;
}