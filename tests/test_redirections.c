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
    minishell("cat -e < tests/test_file.txt", &envp);
    my_free_array(envp);
    remove("tests/test_file.txt");
    cr_expect_stdout_eq_str("Yoo$\n");
}

Test(stdout_redirection, write_on_a_file_instead_of_terminal)
{
    char **envp = my_array_dup(DEFAULT_ENVIRONMENT);
    FILE *file = NULL;

    minishell("echo BONJOUR > tests/test_file.txt", &envp);
    my_free_array(envp);
    file = fopen("tests/test_file.txt", "r");
    cr_expect_file_contents_eq_str(file, "BONJOUR\n");
    fclose(file);
    remove("tests/test_file.txt");
}

Test(stdout_redirection, append_to_a_file)
{
    char **envp = my_array_dup(DEFAULT_ENVIRONMENT);
    FILE *file = NULL;

    minishell("echo BONJOUR >> tests/test_file.txt", &envp);
    minishell("echo Au_Revoir >> tests/test_file.txt", &envp);
    my_free_array(envp);
    file = fopen("tests/test_file.txt", "r");
    cr_expect_file_contents_eq_str(file, "BONJOUR\nAu_Revoir\n");
    fclose(file);
    remove("tests/test_file.txt");
}