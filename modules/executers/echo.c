executor_state echoShell(SlinkedList* parameters){
	
	char* firstWord;
	SLinkedListPeekFront(parameters,&firstWord);
	
	//print the list
	if(streq(firstWord,"echo")){
	
		//iterator to the parameters list
		SIterator it;
		SLinkedListGetIterator(parameters,&it);
		SLinkedListIteratorGoNext(&it);
	
		//print the given line
		while(SLinkedListIteratorHasNext(&it)){

			char* curr;
			SLinkedListIteratorGetNext(&it,&curr);
			printf("%s ", curr);

			SLinkedListIteratorGoNext(&it);
		}
	
		printf("\n");
	
		return executor_DONE;
	}

	return executor_NOOP;
}