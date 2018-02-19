executor_state pwdShell(SlinkedList* parameters){
	
	if(SLinkedListSize(parameters) != 1)
		return executor_NOOP;

	char* firstWord;
	SLinkedListPeekFront(parameters,&firstWord);

	//execute the instruction if only on word and it's equal "pwd"
	if(streq(firstWord,"pwd")){

		char* currentDir = getCurrDir();

		if(currentDir != NULL)
			printf("%s\n",currentDir);
	
		return executor_DONE;
	}

	return executor_NOOP;
}