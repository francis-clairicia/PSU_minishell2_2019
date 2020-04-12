/*
** EPITECH PROJECT, 2019
** PSU_minishell1_2019
** File description:
** exit.c
*/

#include "minishell.h"

int exit_builtin_command(char * const *av UNUSED, char ***envp UNUSED,
    int output_fd)
{
    my_putstr_fd(output_fd, "exit\n");
    return (1);
}