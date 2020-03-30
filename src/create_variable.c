/*
** EPITECH PROJECT, 2019
** PSU_minishell1_2019
** File description:
** create_variable.c
*/

#include "minishell.h"

static void init_var(char *var, int size)
{
    int i = 0;

    while (i < size) {
        var[i] = '\0';
        i += 1;
    }
}

char *create_variable(char const *variable, char const *value)
{
    int len_var = my_strlen(variable);
    int len_value = my_strlen(value);
    int size = len_var + len_value + 2;
    char *var = NULL;

    if (len_var == 0)
        return (NULL);
    var = malloc(sizeof(char) * size);
    if (var != NULL) {
        init_var(var, size);
        my_strcat(var, variable);
        my_strcat(var, (char []){61, '\0'});
        my_strcat(var, value);
    }
    return (var);
}