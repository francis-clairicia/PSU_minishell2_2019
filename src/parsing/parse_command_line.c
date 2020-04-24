/*
** EPITECH PROJECT, 2019
** PSU_minishell1_2019
** File description:
** parse_command_line.c
*/

#include "minishell.h"

static bool is_a_tty_fd(int fd)
{
    return (fd == STDIN_FILENO || fd == STDOUT_FILENO || fd == STDERR_FILENO);
}

command_t init_command_struct(void)
{
    command_t cmd;

    cmd.input_fd = STDIN_FILENO;
    cmd.output_fd = STDOUT_FILENO;
    cmd.error_fd = STDERR_FILENO;
    cmd.argv = NULL;
    return (cmd);
}

command_t parse_command_line(char const *command_line)
{
    char line_copy[my_strlen(command_line) + 1];
    char separators[] = {' ', '\t', '\0'};
    command_t cmd = init_command_struct();

    my_strcpy(line_copy, command_line);
    cmd.input_fd = get_input_fd(line_copy);
    cmd.output_fd = get_output_fd(line_copy);
    cmd.argv = parse_input(line_copy, separators, true);
    return (cmd);
}

void destroy_command(command_t *command)
{
    if (!is_a_tty_fd(command->input_fd) && command->input_fd != -1) {
        close(command->input_fd);
        command->input_fd = STDIN_FILENO;
    }
    if (!is_a_tty_fd(command->output_fd) && command->output_fd != -1) {
        close(command->output_fd);
        command->output_fd = STDOUT_FILENO;
    }
    my_free_array(command->argv);
    command->argv = NULL;
}