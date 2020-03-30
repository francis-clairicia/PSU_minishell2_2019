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

void create_arg(char **command, int first, int last, char quote)
{
    int first_q_i = my_strchr_index(command[first], quote);
    int last_q_i = my_strchr_index(command[last], quote);
    int size_arg = my_strlen(&(command[first][first_q_i + 1])) + last_q_i + 2;
    char *arg = NULL;
    int i = 0;

    for (i = first + 1; i != last; i += 1)
        size_arg += my_strlen(command[i]) + 1;
    arg = my_memset(malloc(sizeof(char) * (size_arg + 1)), '\0', size_arg + 1);
    if (arg == NULL)
        return;
    my_strcat(my_strcat(arg, &(command[first][first_q_i + 1])), " ");
    for (i = first + 1; i != last; i += 1)
        my_strcat(my_strcat(arg, command[i]), " ");
    free(command[first]);
    command[first] = my_strncat(arg, command[last], last_q_i);
    remove_others_args(command, first + 1, last - first);
}