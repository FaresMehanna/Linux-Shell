executor_state exitShell(SlinkedList *parameters) {

    if (SLinkedListSize(parameters) != 1) {
        return executor_NOOP;
    }

    char *firstWord;
    SLinkedListPeekFront(parameters, &firstWord);

    //exit
    if (streq(firstWord, "exit")) {
        printf("\nBye\n");
        memoryClear();
        exit(0);
    }

    return executor_NOOP;
}