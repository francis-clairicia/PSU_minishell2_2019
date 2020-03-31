/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2019
** File description:
** check_line_validity.c
*/

#include "minishell.h"

static bool stdin_redirection(char const *line, int *i)
{
    int index = *i - 1;

    *i += 1;
    if (line[*i] == '<')
        *i += 1;
    while (index >= 0) {
        if (line[index] == '|')
            return (false);
        index -= 1;
    }
    while (line[*i] != '\0' && line[*i] != '|') {
        if (line[*i] == '<')
            return (false);
        *i += 1;
    }
    *i -= 1;
    return (true);
}

static bool stdout_redirection(char const *line, int *i)
{
    *i += 1;
    if (line[*i] == '>')
        *i += 1;
    while (line[*i] != '\0') {
        if (line[*i] == '>' || line[*i] == '|')
            return (false);
        *i += 1;
    }
    *i -= 1;
    return (true);
}

bool check_redirection_validity(char const *line)
{
    int i = 0;

    while (line[i] != '\0') {
        if (line[i] == '>' && stdout_redirection(line, &i) == false) {
            my_putstr_error("Ambiguous output redirect.\n");
            return (false);
        }
        if (line[i] == '<' && stdin_redirection(line, &i) == false) {
            my_putstr_error("Ambiguous input redirect.\n");
            return (false);
        }
        i += 1;
    }
    return (true);
}