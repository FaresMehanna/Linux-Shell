#include "textio.h"

static inline _text_io_state readNextLine(char** destination, FILE* ptr){
    // growable buffer for characters
    char* buffer = NULL;
    // capacity of buffer
    int capacity = 0;
    // number of characters actually in buffer
    int size = 0;
    // max num of characters
    int size_max = 512000;
    // character read or EOF
    int c;

    //NULL file
    if(!ptr)	return _text_io_ERR;
    *destination = smalloc(sizeof(char));
    **destination = '\0';
    // iteratively get characters from standard input, checking for CR (Mac OS), LF (Linux), and CRLF (Windows)
    while ((c = fgetc(ptr)) != '\r' && c != '\n' && c != EOF){
        // grow buffer if necessary
        if (size + 1 > capacity){
            // initialize capacity to 16 (as reasonable for most inputs) and double thereafter
            if (capacity == 0){
                capacity = 16;
            }
            else if (capacity <= (size_max / 2)){
                capacity *= 2;
            }
            else if (capacity < size_max){
                capacity = size_max;
            }
            else{
                sfree(buffer);
                return _text_io_MEMERR;
            }

            // extend buffer's capacity
            char* temp = srealloc(buffer, capacity);
            if (temp == NULL){
                sfree(buffer);
                return _text_io_MEMERR;
            }
            buffer = temp;
        }

        // append current character to buffer
        buffer[size++] = c;
    }

    if(c == EOF){
    	if(size != 0)	*destination = buffer;
    	return _text_io_SUCC_DONE;
    }
    if(size == 0){
    	return _text_io_SUCC;
    }
    if(size == size_max){
    	sfree(buffer);
    	return _text_io_ERR;
    }
    char* toReturn = srealloc(buffer, size + 1);	
    if(!toReturn)	return _text_io_MEMERR;
    toReturn[size] = '\0';
    *destination = toReturn;
    return _text_io_SUCC;
}

static inline void freeStringfunSList(void* Str){
	free(*(char **)Str);
}

static inline _text_io_state addStrToLinkedList(struct string* currWord, SlinkedList* parameters){
    char* toSend;
    if(trimToActSize(currWord) != _text_io_SUCC)   return _text_io_MEMERR; //remove any un-needed space
    getCharPointer(currWord,&toSend);  //get pointer to char*
    if(strlen(toSend) != 0)
        if(SLinkedListAddBack(parameters,&toSend) != _SlinkedList_SUCC) return _text_io_MEMERR; //add to parameter list
    if(createString(currWord) != _text_io_SUCC)    return _text_io_MEMERR; //create new string
    return _text_io_SUCC;
}

static inline _text_io_state getParameters(char* line, SlinkedList* parameters){
	//initalize the n list
	if(InitializeSLinkedList(parameters,sizeof(char*),freeStringfunSList,smalloc,sfree) != _SlinkedList_SUCC)
		return _text_io_MEMERR;
	//pointer & flag
	int inWord = 0;
	int curr = 0;
    int inDubCout = 0;
	//build the string
	struct string currWord;
	createString(&currWord);
	while(line[curr] != '\0'){
		switch(line[curr]){
			case ' ':
				if(!inWord)	break;
                if(inWord && inDubCout){
                    if(addCharToString(&currWord,line[curr]) != _text_io_SUCC)  return _text_io_MEMERR;
                    break;
                }
                if(addStrToLinkedList(&currWord,parameters) != _text_io_SUCC)  return _text_io_MEMERR;
				inWord = 0;	//set flag to new word
			break;
            case '"':
                inWord = 1;
                inDubCout = inDubCout == 0;
                break;
			default:
				inWord = 1;
				if(addCharToString(&currWord,line[curr]) != _text_io_SUCC)	return _text_io_MEMERR;
			break;
		}
		curr++;
	}
	//last word
    if(inWord && addStrToLinkedList(&currWord,parameters) != _text_io_SUCC)  return _text_io_MEMERR;
	return _text_io_SUCC;
}