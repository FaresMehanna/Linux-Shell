//Language Libraries
#include <fcntl.h>
#include <unistd.h>

//Modules
#include "batch.h"
#include "../../memory_manager/memory_manager.h"
#include "../../shell_io/shell_io.h"
#include "../../file_io/file_io.h"
#include "../../text_io/text_io.h"
#include "../../executors/executors_handler.h"

//Data structures
#include "../../../datastructures/singly_linked_list/singly_linked_list.h"

BatchModeState start_batch_mode(char *file_path) {

    //try to open the batch file
    struct FileData file;
    if (set_file(&file, file_path) != file_io_success) {
        print_to_user("BATCH MODE MODULE", "FILE NOT FOUND", shell_error_message);
        return batch_mode_file_error;
    }

    //get input from the file
    char *current_line;
    FileIOState s = read_file(&file, &current_line);

    //make the IO non blocking so we can catch ctrl+D from the stdin
    fcntl(0, F_SETFL, fcntl(0, F_GETFL) | O_NONBLOCK);
    char buff[2];

    //while there is more data
    while (s == file_io_success || s == file_io_last_line) {

        //try to read ctrl+d from stdin
        if (read(0, buff, 1) == 0) {
            memory_clear();
            return batch_mode_success;
        }

        //print the curr Line
        printf(">> %s\n", current_line);

        substitute_variables(&current_line);

        //get the parameters of the line
        SinglyLinkedList parameters;
        if (get_parameters(current_line, &parameters) != text_io_success) {

            print_to_user("BATCH MODE MODULE", "MEMORY ERROR", shell_warning_message);
            close_file(&file);

            return batch_mode_memory_error;
        }

        //execute the line
        execute(&parameters);
        memory_clear();    //clear memory

        if (s == file_io_last_line) {
            break;
        }

        s = read_file(&file, &current_line);    //read again
    }

    //if there is error in reading a line
    if (s == file_io_input_error) {

        print_to_user("BATCH MODE MODULE", "LENGTH EXCEEDED", shell_warning_message);
        close_file(&file);

        return batch_mode_file_error;
    }

    //close the file and return success if everything Ok!
    close_file(&file);

    return batch_mode_success;
}