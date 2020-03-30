/*
** EPITECH PROJECT, 2019
** PSU_minishell1_2019
** File description:
** remove_quotes.c
*/

#include "minishell.h"

void remove_quotes(char **command, int arg, char quote)
{
    int i = 0;
    int j = 0;
    int size = my_strlen(command[arg]) - 2;
    char *new_arg = malloc(sizeof(char) * (size + 1));

    if (new_arg == NULL)
        return;
    while (command[arg][i] != '\0') {
        if (command[arg][i] != quote) {
            new_arg[j] = command[arg][i];
            j += 1;
        }
        i += 1;
    }
    new_arg[j] = '\0';
    free(command[arg]);
    command[arg] = new_arg;
}