/*
** EPITECH PROJECT, 2019
** PSU_minishell1_2019
** File description:
** minishell.c
*/

#include "minishell.h"

static int launch_process(char const *binary, char * const *argv,
    char * const *envp)
{
    int wstatus = 0;
    int child_pid = 0;

    if (binary == NULL)
        return (-1);
    child_pid = fork();
    if (child_pid == 0) {
        if (execve(binary, argv, envp) < 0)
            print_error(argv[0], error_exec(errno));
        return (1);
    }
    waitpid(child_pid, &wstatus, 0);
    if (WIFSIGNALED(wstatus) && WTERMSIG(wstatus) != SIGINT) {
        print_signal(WTERMSIG(wstatus), WCOREDUMP(wstatus));
        return (-1);
    }
    return (0);
}

static int exec_shell_command(char const *command_line, char ***envp)
{
    char *path_to_executable = NULL;
    int status = 0;
    builtin_function_t builtin = NULL;
    char **command = parse_command_line(command_line);

    if (command == NULL)
        return (1);
    builtin = is_builtin(command);
    if (builtin != NULL) {
        status = builtin(command, envp);
    } else {
        path_to_executable = get_path_to_executable(command[0], *envp);
        bind_sigint_signal(PROCESS);
        status = launch_process(path_to_executable, command, *envp);
        free(path_to_executable);
    }
    my_free_array(command);
    return (status);
}

int minishell(char const *command_line, char ***envp)
{
    int i = 0;
    int status = 0;
    int error = 0;
    char **command = my_str_to_word_array(command_line, ";");

    if (command == NULL)
        return (1);
    while (status <= 0 && command[i] != NULL) {
        status = exec_shell_command(command[i], envp);
        i += 1;
        if (status < 0)
            error = 1;
    }
    my_free_array(command);
    return ((!error || status == 1) ? status : -1);
}