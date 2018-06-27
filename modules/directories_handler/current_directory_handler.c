//Language Libraries
#include <unistd.h>

//Modules
#include "current_directory_handler.h"
#include "../memory_manager/memory_manager.h"

char *get_current_working_directory() {

    char *current_working_directory = smalloc(sizeof(char) * 1024);

    if (getcwd(current_working_directory, sizeof(char) * 1024) != NULL) {
        return current_working_directory;
    }

    return NULL;
}

CurrentDirectoryHandlerState set_new_current_working_directory(char* new_working_directory){

    //change the directory
    if (chdir(new_working_directory) == 0) {
        return current_directory_handler_succeed;
    } else {
        return current_directory_handler_error;
    }

}
