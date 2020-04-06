/*
** EPITECH PROJECT, 2019
** PSU_minishell1_2019
** File description:
** create_arg.c
*/

#include "minishell.h"

static void shift_to_left(char **command, int start)
{
    int i = 0;

    for (i = start; command[i] != NULL; i += 1)
        command[i] = command[i + 1];
}

static void remove_others_args(char **command, int start, int nb_deleted)
{
    int i = 0;

    for (i = 0; i < nb_deleted; i += 1) {
        free(command[start]);
        shift_to_left(command, start);
    }
}

static int get_size_new_arg(char **command, int first, int last)
{
    int size = 0;
    int i = 0;

    size += my_strlen(command[first]) + 1;
    for (i = first + 1; i != last; i += 1)
        size += my_strlen(command[i]) + 1;
    size += my_strlen(command[last]);
    return (size);
}

bool create_arg(char **command, int first, int last)
{
    int size_arg = get_size_new_arg(command, first, last);
    char *arg = NULL;
    int i = 0;

    arg = my_memset(malloc(sizeof(char) * (size_arg + 1)), '\0', size_arg + 1);
    if (arg == NULL)
        return (false);
    my_strcat(my_strcat(arg, command[first]), " ");
    for (i = first + 1; i != last; i += 1)
        my_strcat(my_strcat(arg, command[i]), " ");
    free(command[first]);
    command[first] = my_strcat(arg, command[last]);
    remove_others_args(command, first + 1, last - first);
    return (true);
}