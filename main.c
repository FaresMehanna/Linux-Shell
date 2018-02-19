#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

//DS
#include "datastructures/SingleLinkedList/SingleLinkedList.h"
#include "datastructures/HashingwithCahins/ChainHash.h"
//MODULES
#include "modules/dir/dirs.h"
#include "modules/textio/textio.h"
#include "modules/textio/string.h"
#include "modules/shellio/shellio.h"
#include "modules/fileio/fileio.h"
#include "modules/fileio/logger.h"
#include "modules/memorymanger/memmange.h"
#include "modules/modes/batch/batch.h"
#include "modules/modes/interactive/interactive.h"
//executers
#include "modules/executers/executers_handler.h"
#include "modules/executers/echo.h"
#include "modules/executers/exit.h"
#include "modules/executers/cd.h"
#include "modules/executers/execv.h"
#include "modules/executers/history.h"
#include "modules/executers/pwd.h"
#include "modules/executers/expressions.h"
//SIGHANDLERS
#include "modules/sighandlers/sig_handler.h"
#include "modules/sighandlers/sigchld.h"
#include "modules/sighandlers/sigint.h"

//DS
#include "datastructures/SingleLinkedList/SingleLinkedList.c"
#include "datastructures/HashingwithCahins/ChainHash.c"
//Modules
#include "modules/dir/dirs.c"
#include "modules/textio/textio.c"
#include "modules/textio/string.c"
#include "modules/shellio/shellio.c"
#include "modules/fileio/fileio.c"
#include "modules/fileio/logger.c"
#include "modules/memorymanger/memmange.c"
#include "modules/modes/batch/batch.c"
#include "modules/modes/interactive/interactive.c"
//executers
#include "modules/executers/executers_handler.c"
#include "modules/executers/echo.c"
#include "modules/executers/exit.c"
#include "modules/executers/cd.c"
#include "modules/executers/execv.c"
#include "modules/executers/history.c"
#include "modules/executers/pwd.c"
#include "modules/executers/expressions.c"
//SIGHANDLERS
#include "modules/sighandlers/sig_handler.c"
#include "modules/sighandlers/sigchld.c"
#include "modules/sighandlers/sigint.c"

static inline int initializeP(){

	setSIG();	//signals handlers
	
	//initizlize the home Directory
	char* curr = getenv("HOME");
	if(curr == NULL)	return 0;
	
	//set the curr dir
	setenv("1ShellHome",cloneStr(curr),1);
	
	return 1;
}

int main(int argc, char* argv[]){

	//initialize the data needed for the session and signals handlers
	if(!initializeP()){
 		printToUser("MAIN","FAILED IN INITIALIZING SHELL",_shell_io_msg_state_ERROR,0,0);
		return 19;
	}

	//choose between interactive mode and batch mode based on number of arguments given.
    if(argc == 1)
    	startInteractiveMode();
    else if(argc == 2)
    	startBatchMode(argv[1]);
    else
    	printToUser("MAIN","NUM OF ARGUMENT IS INCORRECT",_shell_io_msg_state_ERROR,0,0);
    
    return 0;
}