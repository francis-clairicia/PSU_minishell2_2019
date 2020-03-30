/*
** EPITECH PROJECT, 2019
** PSU_minishell1_2019
** File description:
** builtin_functions.c
*/

#include "minishell.h"

static const struct builtin builtin_functions_list[] = {
    {"cd", cd_builtin_command},
    {"env", env_builtin_command},
    {"exit", exit_builtin_command},
    {"setenv", setenv_builtin_command},
    {"unsetenv", unsetenv_builtin_command},
    {NULL, NULL}
};

builtin_function_t is_builtin(char * const *cmd)
{
    int i = 0;

    if (cmd == NULL)
        return (NULL);
    while (builtin_functions_list[i].command != NULL) {
        if (my_strcmp(cmd[0], builtin_functions_list[i].command) == 0)
            return (builtin_functions_list[i].function);
        i += 1;
    }
    return (NULL);
}