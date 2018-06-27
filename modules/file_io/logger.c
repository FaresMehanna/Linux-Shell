//Language Libraries
#include <stdio.h>
#include <stdlib.h>

//Modules Libraries
#include "logger.h"

LogIOState write_to_log(char *line) {

    FILE *fp;

    //ful path to the file
    char buffer[1024];
    char *directory = getenv("1ShellHome");

    if (!directory) {
        return log_io_file_error;
    }

    //format the log line
    sprintf(buffer, "%s/ShellLog.txt", directory);

    //open the file
    fp = fopen(buffer, "a");
    if (!fp) {
        return log_io_file_error;
    }

    //print the line
    fprintf(fp, "%s\n", line);

    //close the line
    fclose(fp);

    return log_io_success;
}