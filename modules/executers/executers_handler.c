executor_state execute(SlinkedList *parameters) {

    if (SLinkedListSize(parameters) == 0) {
        return executor_DONE;
    }

    if (historyShell(parameters) == executor_DONE) {
        return executor_DONE;
    }

    if (pwdShell(parameters) == executor_DONE) {
        return executor_DONE;
    }

    if (expressionsShell(parameters) == executor_DONE) {
        return executor_DONE;
    }

    if (echoShell(parameters) == executor_DONE) {
        return executor_DONE;
    }

    if (exitShell(parameters) == executor_DONE) {
        return executor_DONE;
    }

    if (cdShell(parameters) == executor_DONE) {
        return executor_DONE;
    }

    return execvShell(parameters);
}