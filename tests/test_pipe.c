/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2019
** File description:
** test_pipe.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "minishell.h"

Test(pipe_redirection, redirect_output_of_process_to_an_another)
{
    char **envp = my_array_dup(DEFAULT_ENVIRONMENT);

    cr_redirect_stdout();
    minishell("echo Hello | cat -e | wc -c", &envp);
    my_free_array(envp);
    cr_expect_stdout_eq_str("7\n");
}