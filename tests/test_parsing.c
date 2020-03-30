/*
** EPITECH PROJECT, 2019
** PSU_minishell1_2019
** File description:
** test_parsing.c
*/

#include <criterion/criterion.h>
#include "minishell.h"

Test(parse_command_line, parse_command_line)
{
    char **argv = parse_command_line("ls -l");

    cr_assert_not_null(argv);
    cr_expect_str_eq(argv[0], "ls");
    cr_expect_str_eq(argv[1], "-l");
    cr_expect_null(argv[2]);
    free(argv);
}

Test(parse_command_line, handle_single_quotes)
{
    char **argv = parse_command_line("ls '-l' 'second arg'");

    cr_assert_not_null(argv);
    cr_expect_str_eq(argv[0], "ls");
    cr_expect_str_eq(argv[1], "-l");
    cr_expect_str_eq(argv[2], "second arg");
    cr_expect_null(argv[3]);
    free(argv);
}

Test(parse_command_line, handle_double_quotes)
{
    char **argv = parse_command_line("ls \"-l\" \"second arg\"");

    cr_assert_not_null(argv);
    cr_expect_str_eq(argv[0], "ls");
    cr_expect_str_eq(argv[1], "-l");
    cr_expect_str_eq(argv[2], "second arg");
    cr_expect_null(argv[3]);
    free(argv);
}