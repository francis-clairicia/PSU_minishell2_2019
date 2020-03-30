/*
** EPITECH PROJECT, 2019
** PSU_minishell1_2019
** File description:
** parse_command_line.c
*/

#include "minishell.h"

static void unify_args(char **command, int arg_with_quote, char quote)
{
    char *actual_arg = command[arg_with_quote];
    int quote_index = my_strchr_index(actual_arg, quote);
    int other_quote = arg_with_quote + 1;

    if (my_strchr_index(&actual_arg[quote_index + 1], quote) >= 0)
        return (remove_quotes(command, arg_with_quote, quote));
    while (command[other_quote] != NULL) {
        if (my_strchr_index(command[other_quote], quote) >= 0)
            return (create_arg(command, arg_with_quote, other_quote, quote));
        other_quote += 1;
    }
}

static char **get_argv(char const *command_line)
{
    int i = 0;
    char separators[] = {' ', '\t', '\0'};
    char **command = my_str_to_word_array(command_line, separators);

    if (command == NULL)
        return (NULL);
    while (command[i] != NULL) {
        if (my_strchr_index(command[i], '\'') >= 0)
            unify_args(command, i, '\'');
        else if (my_strchr_index(command[i], '"') >= 0)
            unify_args(command, i, '"');
        i += 1;
    }
    return (command);
}

command_t parse_command_line(char const *command_line)
{
    char line_copy[my_strlen(command_line) + 1];
    command_t cmd;

    my_strcpy(line_copy, command_line);
    cmd.input_fd = get_input_fd(line_copy);
    cmd.output_fd = get_output_fd(line_copy);
    cmd.argv = get_argv(line_copy);
    return (cmd);
}