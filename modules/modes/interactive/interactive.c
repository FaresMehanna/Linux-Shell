#include "interactive.h"


static inline _interactive_mode_state startInteractiveMode(){
	while(1){
		//write the currDit to screen
		char* currentDir = getCurrDir();
		if(currentDir != NULL)	printf("%s$>> ",currentDir);
		//parameters List
		SlinkedList parameters;
		//get input from the user and validate the user input
		_shell_io_state currState = getInputFromUser(&parameters);
		//check the state of the input
		if(currState != _shell_io_SUCC){
			if(currState == _shell_io_LENGTHEXCED){
				printToUser("INTERACTIVE MODE MODULE","LENGTH EXCEEDED",_shell_io_msg_state_WARNING,0,0);
				memoryClear();
				continue;
			}else if(currState == _shell_io_END){
				printf("\n\nBye\n");
				memoryClear();
				exit(0);
			}else{
				printToUser("INTERACTIVE MODE MODULE","MEMORY ERROR",_shell_io_msg_state_ERROR,0,0);
				return _interactive_mode_MEMERR;
			}
		}
		//execute the command and check the status
		executor_state s = execute(&parameters);
		switch(s){
			case executor_NOOP:
				printToUser("INTERACTIVE MODE MODULE","OPERATION CAN'T BE HANDLED",_shell_io_msg_state_ERROR,0,0);				
			break;
			default: break;			
		}
		//clear the memory
		memoryClear();
	}
}