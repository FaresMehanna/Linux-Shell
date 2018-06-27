#include <stdio.h>
#include <stdlib.h>

//Modules
#include "modules/signals_handler/signals_handler.h"
#include "modules/text_io/string.h"
#include "modules/shell_io/shell_io.h"
#include "modules/modes/interactive/interactive.h"
#include "modules/modes/batch/batch.h"

static inline int initialize_shell() {

    set_signals();    //signals handlers

    //initialize the home Directory
    char *curr = getenv("HOME");
    if (curr == NULL) {
        return 0;
    }

    //set the curr directories_handler
    setenv("1ShellHome", clone_string(curr), 1);

    return 1;
}

int main(int argc, char *argv[]) {

    //initialize the data needed for the session and signals handlers
    if (!initialize_shell()) {
        print_to_user("MAIN", "FAILED IN INITIALIZING SHELL", shell_error_message);
        return 19;
    }

    //choose between interactive mode and batch mode based on number of arguments given.
    if (argc == 1) {
        start_interactive_mode();
    } else if (argc == 2) {
        start_batch_mode(argv[1]);
    } else {
        print_to_user("MAIN", "NUM OF ARGUMENT IS INCORRECT", shell_error_message);
    }
    return 0;
}