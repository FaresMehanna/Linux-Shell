_text_io_state createString(struct string* str){
	
	str->data = smalloc(sizeof(char)*4);
	if(!str->data){
		return _text_io_MEMERR;
	}

	str->data[0] = '\0';
	str->actLength = 1;
	str->memLength = 4;
	
	return _text_io_SUCC;
}

_text_io_state createStringFromCharArr(struct string* str, const char* oStr){

	int len = strlen(oStr) + 1;	//original str size
	str->data = smalloc(sizeof(char)*len);
	
	if(!str->data){
		return _text_io_MEMERR;
	}

	strcpy(str->data,oStr);
	str->actLength = len;
	str->memLength = len;

	return _text_io_SUCC;
}

char* cloneStr(char* x){
	if(!x){
		return NULL;
	}

	char* toReturn = smalloc(sizeof(char)*(strlen(x)+1));
	if(!toReturn){
		return NULL;
	}

	strcpy(toReturn,x);
	return toReturn;
}

_text_io_state freeString(struct string* str){
	sfree(str->data);
	return _text_io_SUCC;
}

_text_io_state growString(struct string* str){

	if(str->actLength != str->memLength){
		return _text_io_SUCC;
	}

	char* new = srealloc(str->data,str->memLength*2);
	if(!new){
		return _text_io_MEMERR;
	}

	str->memLength = str->memLength * 2;
	str->data = new;

	return _text_io_SUCC;
}

_text_io_state addCharToString(struct string* str, char ch){

	if(growString(str) != _text_io_SUCC){
		return _text_io_MEMERR;
	}
	
	str->data[str->actLength-1] = ch;
	str->data[str->actLength] = '\0';
	str->actLength++;

	return _text_io_SUCC;
}

_text_io_state trimToActSize(struct string* str){
	
	if(str->actLength == str->memLength){
		return _text_io_SUCC;
	}
	
	char* new = srealloc(str->data,str->actLength);
	if(!new){
		return _text_io_MEMERR;	
	}

	str->memLength = str->actLength;
	str->data = new;

	return _text_io_SUCC;
}

char sml(char x){
	if(x >= 'A' && x <= 'Z')	return x-'A'+'a';
	return x;
}

int streq(const char* str1, const char* str2){
	int i = 0;
	while(str1[i] != '\0' && str2[i] != '\0'){
		if(sml(str1[i]) != sml(str2[i])){
			return 0;
		}
		i++;
	}
	return str1[i] == str2[i];
}

_text_io_state getCharPointer(struct string* str, char** destination){
	*destination = str->data;
	return _text_io_SUCC;
}