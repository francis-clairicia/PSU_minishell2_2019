/*
** EPITECH PROJECT, 2019
** PSU_minishell1_2019
** File description:
** minishell.c
*/

#include "minishell.h"

int minishell(char const *command_line, char ***envp)
{
    int i = 0;
    int status = 0;
    int error = 0;
    char **command = my_str_to_word_array(command_line, ";");

    if (command == NULL)
        return (1);
    for (i = 0; status <= 0 && command[i] != NULL; i += 1) {
        if (my_str_contains_only(command[i], " \t"))
            continue;
        if (check_redirection_validity(command[i]))
            status = exec_piped_commands(command[i], envp);
        else
            status = -1;
        if (status < 0)
            error = 1;
    }
    my_free_array(command);
    return ((!error || status == 1) ? status : -1);
}