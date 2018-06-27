//Language Libraries
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

//Modules
#include "signal_SIGCHLD.h"
#include "../../modules/file_io/logger.h"
#include "../../modules/shell_io/shell_io.h"

void sigchld_logger(int s, siginfo_t *data, void *d) {

    char buff[128];
    sprintf(buff, "Child %d did finish.", data->si_pid);

    if (write_to_log(buff) == log_io_file_error) {
        print_to_user("SIGCHLD", "LOG FILE ISN'T ACCESSIBLE", shell_warning_message);
    }
}

void SIGCHLD_handler_setter() {
    struct sigaction sigchldHandler;
    sigchldHandler.sa_sigaction = sigchld_logger;
    sigemptyset(&sigchldHandler.sa_mask);
    sigchldHandler.sa_flags = 0;
    sigaction(SIGCHLD, &sigchldHandler, NULL);
}