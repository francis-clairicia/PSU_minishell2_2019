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
    command_t command = parse_command_line("ls -l");

    cr_assert_not_null(command.argv);
    cr_expect_str_eq(command.argv[0], "ls");
    cr_expect_str_eq(command.argv[1], "-l");
    cr_expect_null(command.argv[2]);
    free(command.argv);
}

Test(parse_command_line, handle_single_quotes)
{
    command_t command = parse_command_line("ls '-l' 'second arg'");

    cr_assert_not_null(command.argv);
    cr_expect_str_eq(command.argv[0], "ls");
    cr_expect_str_eq(command.argv[1], "-l");
    cr_expect_str_eq(command.argv[2], "second arg");
    cr_expect_null(command.argv[3]);
    free(command.argv);
}

Test(parse_command_line, handle_double_quotes)
{
    command_t command = parse_command_line("ls \"-l\" \"second arg\"");

    cr_assert_not_null(command.argv);
    cr_expect_str_eq(command.argv[0], "ls");
    cr_expect_str_eq(command.argv[1], "-l");
    cr_expect_str_eq(command.argv[2], "second arg");
    cr_expect_null(command.argv[3]);
    free(command.argv);
}