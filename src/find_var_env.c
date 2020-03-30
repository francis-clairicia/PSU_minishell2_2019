/*
** EPITECH PROJECT, 2019
** PSU_minishell1_2019
** File description:
** find_var_env.c
*/

#include "minishell.h"

int find_var_env(char * const *envp, char const *var)
{
    int len_var = my_strlen(var);
    int i = 0;

    if (envp == NULL || var == NULL)
        return (-1);
    while (envp[i] != NULL) {
        if (my_strncmp(envp[i], var, len_var) == 0)
            return (i);
        i += 1;
    }
    return (-1);
}