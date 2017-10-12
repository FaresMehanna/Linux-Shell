#include "pwd.h"

static inline executor_state pwdShell(SlinkedList* parameters){
	if(SLinkedListSize(parameters) != 1)	return executor_NOOP;
	char* firstWord;
	SLinkedListPeekFront(parameters,&firstWord);
	//exit
	if(streq(firstWord,"pwd")){
		char* currentDir = getCurrDir();
		if(currentDir != NULL)	printf("%s\n",currentDir);
		return executor_DONE;
	}
	return executor_NOOP;
}