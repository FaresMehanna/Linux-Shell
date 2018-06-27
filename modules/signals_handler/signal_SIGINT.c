//Language Libraries
#include <signal.h>
#include <stdio.h>

//Modules
#include "signal_SIGINT.h"

void sigint_handler_clean_and_exit(int s) {
/*NOTHING HAPPENS*/
}

void SIGINT_handler_setter() {
    struct sigaction sigIntHandler;
    sigIntHandler.sa_handler = sigint_handler_clean_and_exit;
    sigemptyset(&sigIntHandler.sa_mask);
    sigIntHandler.sa_flags = 0;
    sigaction(SIGINT, &sigIntHandler, NULL);
}