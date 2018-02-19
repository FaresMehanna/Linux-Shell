executor_state cdShell(SlinkedList* parameters){

	//only two parameters the cd and the wanted directory
	if(SLinkedListSize(parameters) == 2){
	
		//get the first parameter
		char* firstWord;
		SLinkedListPeekFront(parameters,&firstWord);
	
		//check if it's cd
		if(!streq(firstWord,"cd")){
			return executor_NOOP;
		}
		
		//get the wanted dir
		char* curr;
		SLinkedListPeekBack(parameters,&curr);
		
		//change the directory
		if(chdir(curr) == 0){
			return executor_DONE;
		}else{
			return executor_ERR;
		}
	}
	
	return executor_NOOP;
}