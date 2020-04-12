/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2019
** File description:
** get_character_index.c
*/

#include "minishell.h"

static bool between_quotes(char input, char *quote)
{
    char quotes[3] = {'\'', '"', '\0'};
    int quote_index = my_strchr_index(quotes, input);

    if (*quote != 0) {
        if (input == *quote)
            *quote = 0;
        return (true);
    }
    if (quote_index != -1) {
        *quote = quotes[quote_index];
        return (true);
    }
    return (false);
}

int get_character_index(char const *line, char character)
{
    int i = 0;
    char quote = 0;

    for (i = 0; line != NULL && line[i] != '\0'; i += 1) {
        if (!between_quotes(line[i], &quote) && line[i] == character)
            return (i);
    }
    return (-1);
}