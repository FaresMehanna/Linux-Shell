//Modules
#include "executors_handler.h"
#include "change_directory.h"
#include "echo.h"
#include "exit.h"
#include "expressions_evaluator.h"
#include "history.h"
#include "pwd.h"
#include "execute_binary.h"

//Data Structures Libraries
#include "../../datastructures/singly_linked_list/singly_linked_list.h"

ExecutorState execute(SinglyLinkedList *parameters) {

    if (singly_linked_list_size(parameters) == 0) {
        return executor_supported;
    }

    if (history(parameters) == executor_supported) {
        return executor_supported;
    }

    if (pwd(parameters) == executor_supported) {
        return executor_supported;
    }

    if (expressions_evaluator(parameters) == executor_supported) {
        return executor_supported;
    }

    if (echo(parameters) == executor_supported) {
        return executor_supported;
    }

    if (exit_shell(parameters) == executor_supported) {
        return executor_supported;
    }

    if (change_directory(parameters) == executor_supported) {
        return executor_supported;
    }

    return execute_binary(parameters);
}