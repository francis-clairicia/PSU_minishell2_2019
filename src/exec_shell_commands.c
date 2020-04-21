/*
** EPITECH PROJECT, 2019
** PSU_minishell1_2019
** File description:
** exec_shell_commands.c
*/

#include <string.h>
#include "minishell.h"

static int handle_status(int wstatus, int status_pipe)
{
    if (WIFSIGNALED(wstatus)) {
        if (WTERMSIG(wstatus) != SIGINT) {
            print_signal(WTERMSIG(wstatus), WCOREDUMP(wstatus));
            return (-1);
        }
        my_putstr_error("\n");
    }
    return (status_pipe);
}

static int launch_process(char const *binary, command_t commands[],
    char ***envp)
{
    int wstatus = 0;
    int status_pipe = 0;
    int child_pid = 0;
    command_t *command = &commands[0];

    if (binary == NULL || command->input_fd == -1 || command->output_fd == -1)
        return (-1);
    child_pid = fork();
    if (child_pid == 0) {
        dup2(command->input_fd, STDIN_FILENO);
        dup2(command->output_fd, STDOUT_FILENO);
        if (execve(binary, command->argv, *envp) < 0)
            print_error(command->argv[0], error_exec(errno));
        exit(0);
    }
    destroy_command(command);
    if (commands[1].argv != NULL)
        status_pipe = exec_shell_commands(&commands[1], envp);
    waitpid(child_pid, &wstatus, 0);
    return (handle_status(wstatus, status_pipe));
}

static int launch_builtin(builtin_function_t builtin,
    command_t commands[], char ***envp)
{
    char *line = NULL;
    command_t *command = &commands[0];
    int save_stdout = 0;
    int status = 0;
    int status_pipe = 0;

    while (command->input_fd != 0 && get_next_line(&line, command->input_fd));
    free(line);
    if (!(builtin == &exit_builtin_command && commands[1].argv != NULL)) {
        save_stdout = dup(STDOUT_FILENO);
        dup2(command->output_fd, STDOUT_FILENO);
        status = builtin(command->argv, envp);
        dup2(save_stdout, STDOUT_FILENO);
    }
    destroy_command(command);
    if (commands[1].argv != NULL)
        status_pipe = exec_shell_commands(&commands[1], envp);
    return ((status_pipe != 0) ? status_pipe : status);
}

int exec_shell_commands(command_t commands[], char ***envp)
{
    char *path_to_executable = NULL;
    int status = 0;
    builtin_function_t builtin = NULL;
    command_t *command = NULL;

    if (commands == NULL || commands[0].argv == NULL)
        return (-1);
    bind_sigint_signal(PROCESS);
    command = &commands[0];
    builtin = is_builtin(command->argv);
    if (builtin != NULL) {
        status = launch_builtin(builtin, commands, envp);
    } else {
        path_to_executable = get_path_to_executable(command->argv[0], *envp);
        status = launch_process(path_to_executable, commands, envp);
        free(path_to_executable);
    }
    return (status);
}