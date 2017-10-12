#include "sigint.h"

static inline void sigintHandlerCleanAndExit(int s){/*NOTHING HAPPENS*/}

static inline void SIGINThandler(){
	struct sigaction sigIntHandler;
	sigIntHandler.sa_handler = sigintHandlerCleanAndExit;
	sigemptyset(&sigIntHandler.sa_mask);
	sigIntHandler.sa_flags = 0;
	sigaction(SIGINT, &sigIntHandler, NULL);
}