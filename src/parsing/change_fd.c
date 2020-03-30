/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2019
** File description:
** change_fd.c
*/

#include <fcntl.h>
#include "minishell.h"

static void get_file(char *file, char *line, int start, char chevron)
{
    int count = 0;

    my_memset(file, 0, 256);
    line[start] = ' ';
    if (line[start + 1] == chevron)
        line[start + 1] = ' ';
    while (line[start] != '\0' && my_strchr(" \t", line[start]))
        start += 1;
    while (line[start + count] != '\0'
    && !my_strchr(" \t", line[start + count]))
        count += 1;
    my_strncpy(file, &line[start], count);
    my_memset(&line[start], ' ', count);
}

int get_input_fd(char *line)
{
    char file[256];
    int fd = 0;
    int chevron = my_strchr_index(line, '<');

    if (chevron < 0)
        return (0);
    get_file(file, line, chevron, '<');
    fd = open(file, O_RDONLY);
    return ((fd < 0) ? 0 : fd);
}

int get_output_fd(char *line)
{
    char file[256];
    int fd = 0;
    int chevron = my_strchr_index(line, '>');
    int flags = O_CREAT | O_WRONLY;

    if (chevron < 0)
        return (1);
    if (line[chevron + 1] == '>')
        flags |= O_APPEND;
    else
        flags |= O_TRUNC;
    get_file(file, line, chevron, '>');
    fd = open(file, flags, 0644);
    return ((fd < 0) ? 1 : fd);
}