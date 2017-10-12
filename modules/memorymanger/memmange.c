#include "memmange.h"

//function to get hash value for the addresses
static inline unsigned int getHashAddr(void* key, int keysize, long long max){
	return (*(unsigned long long*)key) % max;
}

//function to compare addresses for hash map
static inline int cmpVOIDforHASH (void* p1, void* p2){
	return *(unsigned long long *) p1 == *(unsigned long long *) p2;
}
//function to free addresses
static inline void freeFUNCTIONforHASH (void* p1){
	free(*(void**)p1);
}

static inline void initializeMemoryMap(){
	//malloc size of the hash map
	GLOBAL_MEMORY_STORAGE_.map = malloc(sizeof(HashmapChain));
	if(!GLOBAL_MEMORY_STORAGE_.map) exit(50);
	//initialize the hashmap with the wanted parameters
	InitializeHashmapChain(GLOBAL_MEMORY_STORAGE_.map,
		sizeof(unsigned long long),sizeof(unsigned long long),cmpVOIDforHASH,
		freeFUNCTIONforHASH,NULL,getHashAddr,malloc,free);
}

static inline void* smalloc(size_t size){
	//if no hash map initilaize it
	if(GLOBAL_MEMORY_STORAGE_.map == NULL)	initializeMemoryMap();
	//malloc the wanted size
	void* addr = malloc(size);
	unsigned long long x = (unsigned long long) addr;
	//add the address to the hash map
	if(addr != NULL)
		HashmapChainAddKey(GLOBAL_MEMORY_STORAGE_.map, &x, &x);
	//return the address
	return addr;
}

static inline void sfree(void* ptr){
	//delete the address from the hash map if found and free the data
	int found;
	unsigned long long x = (unsigned long long) ptr;
	HashmapChainDelete(GLOBAL_MEMORY_STORAGE_.map, &x, &found,1);
}

static inline void* srealloc(void* ptr, size_t newSize){
	//if no ptr==NULL then use smalloc
	if(!ptr)	return smalloc(newSize);
	//realloc new data
	void* addr = realloc(ptr,newSize);
	unsigned long long x = (unsigned long long) addr;
	unsigned long long y = (unsigned long long) ptr;
	int found;
	//if the reallocation succ and return diffrenet value the remove the old
	//without freeing it and add new one
	if(addr != NULL && x != y){
		HashmapChainDelete(GLOBAL_MEMORY_STORAGE_.map,&y,&found,0);
		HashmapChainAddKey(GLOBAL_MEMORY_STORAGE_.map, &x, &x);
	}
	return addr;
}

static inline void memoryClear(){
	if(GLOBAL_MEMORY_STORAGE_.map == NULL)	return;
	//remove the hashmap with all it's keys
	DisposeHashmapChain(GLOBAL_MEMORY_STORAGE_.map);
	//free the map itself
	free(GLOBAL_MEMORY_STORAGE_.map);
	GLOBAL_MEMORY_STORAGE_.map = NULL;	//protect the map
}