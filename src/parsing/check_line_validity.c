/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2019
** File description:
** check_line_validity.c
*/

#include "minishell.h"

static bool valid_pipes(char const *line, char * const *commands)
{
    int nb_commands = my_array_len(commands);
    int nb_pipes = 0;
    int index = 0;
    bool status = true;

    while ((index = get_character_index(line, '|')) != -1) {
        nb_pipes += 1;
        line = &line[index + 1];
    }
    status = (nb_commands == (nb_pipes + 1));
    for (index = 0; status == true && commands[index] != NULL; index += 1) {
        if (my_str_contains_only(commands[index], " \t"))
            status = false;
    }
    if (status == false)
        my_putstr_error("Invalid null command.\n");
    return (status);
}

static bool check_stdin_redirection(char * const *commands, int index)
{
    char line_copy[my_strlen(commands[index]) + 1];
    int chevron_index = my_strchr_index(commands[index], '<');

    my_strcpy(line_copy, commands[index]);
    line_copy[chevron_index] = ' ';
    if (line_copy[chevron_index + 1] == '<')
        line_copy[chevron_index + 1] = ' ';
    if (index - 1 >= 0 || get_character_index(line_copy, '<') >= 0) {
        my_putstr_error("Ambiguous input redirect.\n");
        return (false);
    }
    return (true);
}

static bool check_stdout_redirection(char * const *commands, int index)
{
    char line_copy[my_strlen(commands[index]) + 1];
    int nb_commands = my_array_len(commands);
    int chevron_index = my_strchr_index(commands[index], '>');

    my_strcpy(line_copy, commands[index]);
    line_copy[chevron_index] = ' ';
    if (line_copy[chevron_index + 1] == '>')
        line_copy[chevron_index + 1] = ' ';
    if (index + 1 != nb_commands || get_character_index(line_copy, '>') >= 0) {
        my_putstr_error("Ambiguous output redirect.\n");
        return (false);
    }
    return (true);
}

static bool check_redirection(char * const *commands, int line_index)
{
    int input_index = get_character_index(commands[line_index], '<');
    int output_index = get_character_index(commands[line_index], '>');

    if (input_index == -1 && output_index == -1)
        return (true);
    if (input_index == -1)
        return (check_stdout_redirection(commands, line_index));
    if (output_index == -1)
        return (check_stdin_redirection(commands, line_index));
    if (input_index < output_index)
        return (check_stdin_redirection(commands, line_index));
    return (check_stdout_redirection(commands, line_index));
}

bool check_redirection_validity(char const *line)
{
    int i = 0;
    char **piped_commands = parse_input(line, "|", false);
    bool status = true;

    if (piped_commands == NULL || !valid_pipes(line, piped_commands))
        status = false;
    while (status == true && piped_commands[i] != NULL) {
        status &= check_redirection(piped_commands, i);
        i += 1;
    }
    my_free_array(piped_commands);
    return (status);
}