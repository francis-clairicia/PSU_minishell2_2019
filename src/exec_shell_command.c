/*
** EPITECH PROJECT, 2019
** PSU_minishell1_2019
** File description:
** exec_shell_command.c
*/

#include "minishell.h"

static int launch_process(char const *binary, command_t command,
    char * const *envp)
{
    int wstatus = 0;
    int child_pid = 0;

    if (binary == NULL || command.input_fd == -1 || command.output_fd == -1)
        return (-1);
    child_pid = fork();
    if (child_pid == 0) {
        dup2(command.input_fd, 0);
        dup2(command.output_fd, 1);
        if (execve(binary, command.argv, envp) < 0)
            print_error(command.argv[0], error_exec(errno));
        return (1);
    }
    waitpid(child_pid, &wstatus, 0);
    if (WIFSIGNALED(wstatus) && WTERMSIG(wstatus) != SIGINT) {
        print_signal(WTERMSIG(wstatus), WCOREDUMP(wstatus));
        return (-1);
    }
    return (0);
}

int exec_shell_command(command_t command, char ***envp)
{
    char *path_to_executable = NULL;
    int status = 0;
    builtin_function_t builtin = NULL;

    if (command.argv == NULL) {
        my_putstr_error("Invalid null command.\n");
        return (-1);
    }
    builtin = is_builtin(command.argv);
    if (builtin != NULL) {
        status = builtin(command.argv, envp);
    } else {
        path_to_executable = get_path_to_executable(command.argv[0], *envp);
        bind_sigint_signal(PROCESS);
        status = launch_process(path_to_executable, command, *envp);
        free(path_to_executable);
    }
    return (status);
}