#include "execv.h"

static inline char* getFullPath(SlinkedList* parameters){
	
	char* binaryName;
	SLinkedListPeekFront(parameters,&binaryName);
	int len = strlen(binaryName);

	//handle full path given
	if(binaryName[0] == '/'){
		if(access(binaryName, F_OK) == 0)		return binaryName;
		return NULL;
	}

	//handle ./execution
	if(len >= 2 && binaryName[0] == '.' && binaryName[1] == '/'){
		int counter = 2;
		char* curr = getCurrDir();	//get current directory
		if(curr == NULL)	return NULL;
		struct string path;	//string to build the path
		if(createStringFromCharArr(&path,curr) != _text_io_SUCC)	return NULL;	//create the string from the curr dir
		//add the words to the string
		if(addCharToString(&path,'/') != _text_io_SUCC)	return NULL;
		while(binaryName[counter] != '\0')	if(addCharToString(&path,binaryName[counter++]) != _text_io_SUCC)	return NULL;
		//get the string and return it
		char* fullPath;
		trimToActSize(&path);
		getCharPointer(&path,&fullPath);
		if(access(fullPath, F_OK) == 0)		return binaryName;
		return NULL;
	}

	//TRY to get the path from $PATH
	char* PATHORIGINAL = getenv("PATH");
	if(!PATHORIGINAL)	return NULL;
	char* PATH = cloneStr(PATHORIGINAL);
	char * pch;
	pch = strtok(PATH,":");

	while (pch != NULL)
	{
		int counter = 0;
		struct string path;
		if(createStringFromCharArr(&path,pch) != _text_io_SUCC)	return NULL;
		addCharToString(&path,'/');
		while(binaryName[counter] != '\0')	if(addCharToString(&path,binaryName[counter++]) != _text_io_SUCC)	return NULL;

		char* fullPath;
		trimToActSize(&path);
		getCharPointer(&path,&fullPath);

		if(access(fullPath, F_OK) == 0)		
			return fullPath;

		pch = strtok (NULL, ":");
	}
	return NULL;
}

static inline void executeShell(char* path, char** params, int background){
    pid_t pid = fork();
    int status;

    if (pid == 0){
        execv(path,params);
        printToUser("CHILD PROCESS","CAN'T FORK",_shell_io_msg_state_ERROR,0,0);
        exit(EXIT_FAILURE);
    }
    else if (pid > 0){
    	//log creation of the process
		char buff[128];
		sprintf(buff,"Child %d did start.",pid);
		if(writeToLog(buff) == _log_io_FILE_ERR)	printToUser("EXECV EXECUTOR","LOG FILE ISN'T ACCESSIBLE" ,_shell_io_msg_state_WARNING,0,0);
    	if(!background)
    		do{
				waitpid (pid, &status, WUNTRACED);
			}while(!WIFEXITED(status) && !WIFSIGNALED(status));
		else
			printToUser("EXECV EXECUTOR","CHILD PROCESS STARETED IN BACKGROUND" ,_shell_io_msg_state_INFO,0,0);

    }else
        printToUser("PARENT PROCESS","CAN'T FORK",_shell_io_msg_state_ERROR,0,0);
}

static inline executor_state execvShell(SlinkedList* parameters){
	char* fullP = getFullPath(parameters);
	if(!fullP)	return executor_NOOP;
	int foreBackGround = 0;
	char* last;
	
	SLinkedListPeekBack(parameters,&last);
	if(streq(last,"&"))	foreBackGround = 1;

	char* params[SLinkedListSize(parameters)-foreBackGround+1];

	SIterator it;
	SLinkedListGetIterator(parameters,&it);
	int counter = 0;
	
	//get the parameter list for execv
	while(SLinkedListIteratorHasNext(&it)){
		char* curr;
		SLinkedListIteratorGetNext(&it,&curr);
		SLinkedListIteratorGoNext(&it);
		params[counter++] = curr;
	}
	params[counter-foreBackGround] = NULL;

	//execute the new process
	executeShell(fullP,params,foreBackGround);

	return executor_DONE;	
}