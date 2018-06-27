//Language Libraries
#include <stdio.h>

//Modules Libraries
#include "file_io.h"
#include "../text_io/text_io.h"

FileIOState close_file(struct FileData *file) {

    if (file->fp) {
        fclose(file->fp);
    }

    file->fp = NULL;

    return file_io_success;
}

FileIOState set_file(struct FileData *file, char *destination) {

    //open the file
    file->fp = fopen(destination, "r");

    if (!file->fp) {
        return file_io_file_not_found;
    }

    return file_io_success;
}

FileIOState read_file(struct FileData *file, char **destination_line) {

    char *line;
    TextIOState s = read_next_line(&line, file->fp);
    int done = 0;

    if (s == text_io_last_line) {
        done = 1;
    } else if (s != text_io_success) {
        close_file(file);
        return file_io_input_error;
    }

    *destination_line = line;

    if (done) {
        return file_io_last_line;
    }

    return file_io_success;
}