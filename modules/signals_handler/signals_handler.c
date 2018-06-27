//Modules
#include "signals_handler.h"
#include "signal_SIGINT.h"
#include "signal_SIGCHLD.h"

void set_signals() {
    SIGINT_handler_setter();
    SIGCHLD_handler_setter();
}