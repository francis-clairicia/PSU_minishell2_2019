/*
** EPITECH PROJECT, 2019
** PSU_minishell1_2019
** File description:
** parse_command_line.c
*/

#include "minishell.h"

static bool unify_args(char **command, int arg, char quote)
{
    char *actual_arg = command[arg];
    int quote_index = my_strchr_index(actual_arg, quote);
    int other_quote = arg + 1;

    if (my_strchr_index(&actual_arg[quote_index + 1], quote) >= 0)
        return (remove_quotes(command, arg, quote));
    while (command[other_quote] != NULL) {
        if (my_strchr_index(command[other_quote], quote) >= 0)
            return (create_arg(command, arg, other_quote));
        other_quote += 1;
    }
    my_putstr_error("Unmatched '");
    write(2, &quote, 1);
    my_putstr_error("'.\n");
    return (false);
}

static char **get_argv(char const *command_line)
{
    int i = 0;
    char separators[] = {' ', '\t', '\0'};
    char **command = my_str_to_word_array(command_line, separators);
    bool error = false;

    if (command == NULL)
        return (NULL);
    while (!error && command[i] != NULL) {
        if (my_strchr_index(command[i], '\'') >= 0)
            error = !unify_args(command, i, '\'');
        else if (my_strchr_index(command[i], '"') >= 0)
            error = !unify_args(command, i, '"');
        else
            i += 1;
    }
    if (error)
        my_free_array(command);
    return ((error) ? (NULL) : (command));
}

static command_t init_command_struct(void)
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
    if (cmd.input_fd >= 0)
        cmd.output_fd = get_output_fd(line_copy);
    cmd.argv = get_argv(line_copy);
    return (cmd);
}