static inline executor_state historyShellWrite(SlinkedList* parameters){

	FILE *fp;
	char buffer[1024];

	//get the path to the history file
	char* dir = getenv("1ShellHome");
	if(!dir)
		return executor_ERR;
	
	//get complete path
	sprintf(buffer,"%s/ShellHistory.txt",dir);

	//open the history file for appending
	fp = fopen(buffer, "a");
	if(!fp)	return executor_ERR;

	//write the line to the history file
	SIterator it;
	SLinkedListGetIterator(parameters,&it);
	
	while(SLinkedListIteratorHasNext(&it)){
	
		char* curr;
		SLinkedListIteratorGetNext(&it,&curr);
		SLinkedListIteratorGoNext(&it);
		fprintf(fp,"%s ", curr);
	}

	fprintf(fp,"\n");
	
	//close and return succ
	fclose(fp);
	
	return executor_DONE;
}

static inline executor_state historyShellRead(SlinkedList* parameters){
	
	if(SLinkedListSize(parameters) != 1)
		return executor_NOOP;
	
	char* firstWord;
	SLinkedListPeekFront(parameters,&firstWord);
	
	//history
	if(!streq(firstWord,"history"))
		return executor_NOOP;

	char buffer[1024];
	
	//get the path to the history file
	char* dir = getenv("1ShellHome");
	if(!dir)
		return executor_ERR;
	
	sprintf(buffer,"%s/ShellHistory.txt",dir);

	//try to read history if there is history
	struct fileDate file;
	if(setFile(&file,buffer) != _file_io_SUCC)
		return executor_DONE;

	//get input from the file
	char* currLine;
	while(readFile(&file,&currLine) == _file_io_SUCC)
			printf("%s\n", currLine);
	
	//close and return succ
	closeFile(&file);
	
	return executor_DONE;
}

executor_state historyShell(SlinkedList* parameters){

	historyShellWrite(parameters);

	return historyShellRead(parameters);
}