#include "shellio.h"

static inline _shell_io_state getInputFromUser(SlinkedList* parameters){
	char* line;
	//handle any memory error
	_text_io_state s = readNextLine(&line,stdin);
	substitueVars(&line);
	if(s == _text_io_SUCC_DONE && feof(stdin))	return _shell_io_END;
	if(s == _text_io_ERR || s == _text_io_MEMERR)	return _shell_io_MEMERR;
	int len = strlen(line);
	//handle big instructions
	if(len > 512)
		return _shell_io_LENGTHEXCED;
	//get the parameters
	if(getParameters(line,parameters) != _text_io_SUCC)		return _shell_io_MEMERR;
	return _shell_io_SUCC;	//return succ
}


static inline _shell_io_state printToUser(char* identifier, char* message, shell_io_msg_state state, int o1, int o2){
	switch(state){
		case _shell_io_msg_state_INFO:
			printf("INFO ::: ");
		break;
		case _shell_io_msg_state_WARNING:
			printf("WARNING ::: ");
		break;
		case _shell_io_msg_state_ERROR:
			printf("ERROR ::: ");
		break;
	}
	printf("%s :: %s.\n",identifier,message);
	if(o1)	free(identifier);
	if(o2)	free(message);
	return _shell_io_SUCC;
}

static inline _shell_io_state validateVarChar(char varChar, int index){
	if(varChar >= 'a' && varChar <= 'z')	return _shell_io_SUCC;
	if(varChar >= 'A' && varChar <= 'Z')	return _shell_io_SUCC;
	if(index && varChar >= '0' && varChar <= '9')	return _shell_io_SUCC;
	return _shell_io_ERR;
}

static inline int handleVar(char* oStr, struct string* str, int index, int len){
	
	struct string toReturn;
	createString(&toReturn);

	int i;
	for(i=index;i<len;i++){
		if(validateVarChar(oStr[i],i-index) == _shell_io_SUCC){
			addCharToString(&toReturn,oStr[i]);
		}else	break;
	}
	int offset = i-index;

	char* variableName;
	trimToActSize(&toReturn);
	getCharPointer(&toReturn,&variableName);

	char* data = getenv(variableName);
	if(data == NULL)	return offset;
	i=0;
	while(data[i++] != '\0')	addCharToString(str,data[i-1]);
	return offset;

}

static inline _shell_io_state substitueVars(char** varChar){
	//get length and the string
	int len = strlen(*varChar);
	int lenty;
	char* str = *varChar;
	//create string to be manibulated and return
	struct string toReturn;
	createString(&toReturn);

	for(int i=0;i<len;i++){
		switch(str[i]){
			case '$':
				if(i != 0 && str[i-1] == '\\'){
					addCharToString(&toReturn,str[i]);
					break;
				}
				lenty = handleVar(str,&toReturn,i+1,len);
				if(lenty == 0)	addCharToString(&toReturn,str[i]);
				else	i += lenty;
			break;
			case '\\':
			break;
			case '~':
				//substitue with $HOME
				if((i-1 >= 0 && str[i-1] == ' ' && i+1 == len) ||
				   (i-1 >= 0 && str[i-1] == ' ' && i+1 < len && str[i+1] == ' ') ||
				   (i-1 >= 0 && str[i-1] == ' ' && i+1 < len && str[i+1] == '/')){
					char* homeTemp = getenv("HOME");
					lenty = 0;
					while(homeTemp[lenty] != '\0')	addCharToString(&toReturn,homeTemp[lenty++]);
				}else	addCharToString(&toReturn,str[i]);
			break;
			
			default:
				addCharToString(&toReturn,str[i]);
			break;
		}
	}

	trimToActSize(&toReturn);
	getCharPointer(&toReturn,varChar);
	return _shell_io_SUCC;
}