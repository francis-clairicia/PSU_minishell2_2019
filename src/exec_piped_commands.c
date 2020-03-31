/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2019
** File description:
** exec_piped_commands.c
*/

#include <stdio.h>
#include "minishell.h"

static int occurence_in_str(char const *str, char c)
{
    int i = 0;
    int count = 0;

    for (i = 0; str[i] != '\0'; i += 1)
        count += (str[i] == c);
    return (count);
}

static bool link_all_commands(command_t commands[], int nb_commands)
{
    int pipefd[2];
    int i = 0;

    for (i = 1; i < nb_commands; i += 1) {
        if (pipe(pipefd) != 0)
            return (false);
        commands[i - 1].output_fd = pipefd[1];
        commands[i].input_fd = pipefd[0];
    }
    return (true);
}

static bool destroy_command(command_t command)
{
    if (command.input_fd != 0 && command.input_fd != -1)
        close(command.input_fd);
    if (command.output_fd != 1 && command.output_fd != 2
    && command.output_fd != -1)
        close(command.output_fd);
    my_free_array(command.argv);
    return (false);
}

static bool init_commands(command_t commands[], char * const *piped_commands)
{
    int i = 0;

    for (i = 0; piped_commands[i] != NULL; i += 1) {
        commands[i] = parse_command_line(piped_commands[i]);
        if (commands[i].argv == NULL) {
            my_putstr_error("Invalid null command.\n");
            return (destroy_command(commands[i]));
        }
        if (commands[i].input_fd < 0 || commands[i].output_fd < 0)
            return (destroy_command(commands[i]));
    }
    return (true);
}

int exec_piped_commands(char const *command_line, char ***envp)
{
    char **piped_commands = my_str_to_word_array(command_line, "|");
    int nb_commands = my_array_len(piped_commands);
    command_t commands[(nb_commands == 0) ? 1 : nb_commands];
    int i = 0;
    int status = 0;

    if (nb_commands <= occurence_in_str(command_line, '|')) {
        my_putstr_error("Invalid null command.\n");
        return (-1);
    }
    if (!init_commands(commands, piped_commands))
        return (-1);
    if (!link_all_commands(commands, nb_commands))
        return (-1);
    for (i = 0; i < nb_commands && status == 0; i += 1) {
        status = exec_shell_command(commands[i], envp);
        destroy_command(commands[i]);
    }
    my_free_array(piped_commands);
    return (status);
}