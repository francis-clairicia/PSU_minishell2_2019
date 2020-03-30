/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2019
** File description:
** test_redirections.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <fcntl.h>
#include "minishell.h"

Test(stdin_redirection, read_a_file_as_standard_input)
{
    char **envp = my_array_dup(DEFAULT_ENVIRONMENT);
    int fd = open("tests/test_file.txt", O_CREAT | O_WRONLY, 0664);

    cr_redirect_stdout();
    my_putstr_fd(fd, "Yoo\n");
    close(fd);
    cr_expect_eq(minishell("cat -e < tests/test_file.txt", &envp), 0);
    my_free_array(envp);
    remove("tests/test_file.txt");
    cr_expect_stdout_eq_str("Yoo$\n");
}

Test(stdin_redirection, print_error_if_there_is_no_file)
{
    char **envp = my_array_dup(DEFAULT_ENVIRONMENT);

    cr_redirect_stderr();
    cr_expect_eq(minishell("cat < ", &envp), -1);
    my_free_array(envp);
    cr_expect_stderr_eq_str("Missing name for redirect.\n");
}

Test(stdin_redirection, print_error_if_can_t_open_file)
{
    char **envp = my_array_dup(DEFAULT_ENVIRONMENT);

    cr_redirect_stderr();
    cr_expect_eq(minishell("cat < unknown_file.unknown", &envp), -1);
    my_free_array(envp);
    cr_expect_stderr_eq_str("unknown_file.unknown: "
        "No such file or directory.\n");
}