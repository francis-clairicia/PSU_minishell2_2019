/*
** EPITECH PROJECT, 2019
** PSU_minishell1_2019
** File description:
** remove_quotes.c
*/

#include "minishell.h"

static void set_new_arg(char *new_arg, char const *command, char quote)
{
    int i = 0;
    int j = 0;
    int nb_quotes = 0;

    while (command[i] != '\0') {
        if (command[i] != quote || nb_quotes >= 2) {
            new_arg[j] = command[i];
            j += 1;
        } else {
            nb_quotes += 1;
        }
        i += 1;
    }
    new_arg[j] = '\0';
}

bool remove_quotes(char **command, int arg, char quote)
{
    int size = my_strlen(command[arg]) - 2;
    char *new_arg = malloc(sizeof(char) * (size + 1));

    if (new_arg == NULL)
        return (false);
    set_new_arg(new_arg, command[arg], quote);
    free(command[arg]);
    command[arg] = new_arg;
    return (true);
}