_file_io_state closeFile(struct fileDate *file) {

    if (file->fp) {
        fclose(file->fp);
    }

    file->fp = NULL;

    return _file_io_SUCC;
}

_file_io_state setFile(struct fileDate *file, char *destination) {

    //open the file
    file->fp = fopen(destination, "r");

    if (!file->fp) {
        return _file_io_FILE_NFOUND;
    }

    return _file_io_SUCC;
}

_file_io_state readFile(struct fileDate *file, char **toReturnline) {

    char *line;
    _text_io_state s = readNextLine(&line, file->fp);
    int done = 0;

    if (s == _text_io_SUCC_DONE) {
        done = 1;
    } else if (s != _text_io_SUCC) {
        closeFile(file);
        return _file_io_FILE_INPUTERR;
    }

    *toReturnline = line;

    if (done) {
        return _file_io_DONE;
    }

    return _file_io_SUCC;
}