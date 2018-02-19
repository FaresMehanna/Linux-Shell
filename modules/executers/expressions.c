executor_state expressionsShell(SlinkedList* parameters){

	//get the first word
	char* firstWord;
	SLinkedListPeekFront(parameters,&firstWord);

	//export used
	if(SLinkedListSize(parameters) == 2){

		//set the expression to the second argument
		if(streq(firstWord,"export")){
			SLinkedListPeekBack(parameters,&firstWord);
		}else{
			return executor_NOOP;
		}

	}else if(SLinkedListSize(parameters) != 1){		//expression only in one word
		return executor_NOOP;
	}
	
	//make a clone from the word
	char* clone = cloneStr(firstWord);
	int oldLen = strlen(clone);
	
	//get the key
	char* key = strtok(clone,"=");
	if(key == NULL){
		return executor_NOOP;
	}
	
	key = cloneStr(key);
	
	//validate the key
	int len = strlen(key);
	
	for(int i=0;i<len;i++){
		if(validateVarChar(key[i],i) != _shell_io_SUCC){
			return executor_NOOP;
		}
	}

	//check the value
	int nKey = strlen(key);
	char* value;

	if(oldLen == nKey){
		return executor_NOOP;
	}else if(oldLen == nKey+1){
		value = cloneStr("");
	}else{
		value = firstWord+strlen(key)+1;
	}

	substitueVars(&value);

	//add to the env variables
	printToUser("EXPRESSIONS EXECUTER","New variable has been defined",_shell_io_msg_state_INFO,0,0);
	
	setenv(key,value,1);
	
	//return done
	return executor_DONE;
}