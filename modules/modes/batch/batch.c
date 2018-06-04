
_batch_mode_state startBatchMode(char *filePath) {

    //try to open the batch file
    struct fileDate file;
    if (setFile(&file, filePath) != _file_io_SUCC) {
        printToUser("BATCH MODE MODULE", "FILE NOT FOUND", _shell_io_msg_state_ERROR);
        return _batch_mode_FILEERR;
    }

    //get input from the file
    char *currLine;
    _file_io_state s = readFile(&file, &currLine);

    //make the IO non blocking so we can catch ctrl+D from the stdin
    fcntl(0, F_SETFL, fcntl(0, F_GETFL) | O_NONBLOCK);
    char buff[2];

    //while there is more data
    while (s == _file_io_SUCC || s == _file_io_DONE) {

        //try to read ctrl+d from stdin
        if (read(0, buff, 1) == 0) {
            memoryClear();
            return _batch_mode_SUCC;
        }

        //print the curr Line
        printf(">> %s\n", currLine);

        substitueVars(&currLine);

        //get the parameters of the line
        SlinkedList parameters;
        if (getParameters(currLine, &parameters) != _text_io_SUCC) {

            printToUser("BATCH MODE MODULE", "MEMORY ERROR", _shell_io_msg_state_WARNING);
            closeFile(&file);

            return _batch_mode_MEMERR;
        }

        //execute the line
        execute(&parameters);
        memoryClear();    //clear memory

        if (s == _file_io_DONE) {
            break;
        }

        s = readFile(&file, &currLine);    //read again
    }

    //if there is error in reading a line
    if (s == _file_io_FILE_INPUTERR) {

        printToUser("BATCH MODE MODULE", "LENGTH EXCEEDED", _shell_io_msg_state_WARNING);
        closeFile(&file);

        return _batch_mode_FILEERR;
    }

    //close the file and return succ if everything Ok!
    closeFile(&file);

    return _batch_mode_SUCC;
}