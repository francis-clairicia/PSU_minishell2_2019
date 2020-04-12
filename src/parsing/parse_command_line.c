/*
** EPITECH PROJECT, 2019
** PSU_minishell1_2019
** File description:
** parse_command_line.c
*/

#include "minishell.h"

static char **get_argv(char const *command_line)
{
    char separators[] = {' ', '\t', '\0'};
    char **command = parse_input(command_line, separators, true);

    return (command);
}

command_t init_command_struct(void)
{
    command_t cmd;

    cmd.input_fd = 0;
    cmd.output_fd = 1;
    cmd.argv = NULL;
    return (cmd);
}

command_t parse_command_line(char const *command_line)
{
    char line_copy[my_strlen(command_line) + 1];
    command_t cmd = init_command_struct();

    my_strcpy(line_copy, command_line);
    cmd.input_fd = get_input_fd(line_copy);
    cmd.output_fd = get_output_fd(line_copy);
    cmd.argv = get_argv(line_copy);
    return (cmd);
}

void destroy_command(command_t *command)
{
    if (command->input_fd != 0 && command->input_fd != -1) {
        close(command->input_fd);
        command->input_fd = 0;
    }
    if (command->output_fd != 1 && command->output_fd != 2
    && command->output_fd != -1) {
        close(command->output_fd);
        command->output_fd = 1;
    }
    my_free_array(command->argv);
    command->argv = NULL;
}