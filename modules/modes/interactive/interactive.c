//Language Libraries
#include <stdio.h>
#include <stdlib.h>

//Modules
#include "interactive.h"
#include "../../memory_manager/memory_manager.h"
#include "../../shell_io/shell_io.h"
#include "../../executors/executors_handler.h"
#include "../../directories_handler/current_directory_handler.h"

//Data structures
#include "../../../datastructures/singly_linked_list/singly_linked_list.h"

InteractiveModeState start_interactive_mode() {

    while (1) {
        //write the currDit to screen
        char *current_directory = get_current_working_directory();
        if (current_directory != NULL) {
            printf("%s$>> ", current_directory);
        }

        //parameters List
        SinglyLinkedList parameters;
        //get input from the user and validate the user input
        ShellIOState current_state = get_input_from_user(&parameters);

        //check the state of the input
        if (current_state != shell_io_success) {

            if (current_state == shell_io_length_exceeded) {
                print_to_user("INTERACTIVE MODE MODULE", "LENGTH EXCEEDED", shell_warning_message);
                memory_clear();
                continue;

            } else if (current_state == shell_io_last_line) {
                printf("\n\nBye\n");
                memory_clear();
                exit(0);

            } else {
                print_to_user("INTERACTIVE MODE MODULE", "MEMORY ERROR", shell_error_message);
                return interactive_mode_memory_error;
            }
        }

        //execute the command and check the status
        ExecutorState s = execute(&parameters);

        switch (s) {
            case executor_not_supported:
                print_to_user("INTERACTIVE MODE MODULE", "OPERATION CAN'T BE HANDLED", shell_error_message);
                break;

            default:
                break;
        }

        //clear the memory
        memory_clear();
    }
}