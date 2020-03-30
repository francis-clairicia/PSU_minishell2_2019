/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2019
** File description:
** exec_piped_commands.c
*/

#include <stdio.h>
#include "minishell.h"

static bool link_commands(command_t *cmd_1, command_t *cmd_2)
{
    int pipefd[2];

    if (pipe(pipefd) != 0)
        return (false);
    cmd_1->output_fd = pipefd[1];
    cmd_2->input_fd = pipefd[0];
    return (true);
}

static bool link_all_commands(command_t commands[], int nb_commands)
{
    int i = 0;

    for (i = 1; i < nb_commands; i += 1) {
        if (!link_commands(&commands[i - 1], &commands[i]))
            return (false);
    }
    return (true);
}

static void destroy_all_commands(command_t commands[], int nb_commands)
{
    int i = 0;

    for (i = 0; i < nb_commands; i += 1) {
        if (commands[i].input_fd != 0)
            close(commands[i].input_fd);
        my_free_array(commands[i].argv);
    }
}

int exec_piped_commands(char const *command_line, char ***envp)
{
    char **piped_commands = my_str_to_word_array(command_line, "|");
    int nb_commands = my_array_len(piped_commands);
    command_t commands[(nb_commands == 0) ? 1 : nb_commands];
    int i = 0;
    int status = 0;

    if (piped_commands == NULL)
        return (-1);
    for (i = 0; piped_commands[i] != NULL; i += 1)
        commands[i] = parse_command_line(piped_commands[i]);
    link_all_commands(commands, nb_commands);
    for (i = 0; i < nb_commands; i += 1) {
        status = exec_shell_command(commands[i], envp);
        if (commands[i].output_fd != 1 && commands[i].output_fd != 2)
            close(commands[i].output_fd);
        if (status != 0)
            break;
    }
    my_free_array(piped_commands);
    destroy_all_commands(commands, nb_commands);
    return (status);
}