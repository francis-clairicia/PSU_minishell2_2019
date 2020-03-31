/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2019
** File description:
** change_fd.c
*/

#include <fcntl.h>
#include "minishell.h"

static void get_file(char *file, char *line, int start, char chevrons[2])
{
    char non_valid[] = {' ', '\t', chevrons[1], '\0'};
    int count = 0;

    my_memset(file, 0, 256);
    line[start] = ' ';
    if (line[start + 1] == chevrons[0])
        line[start + 1] = ' ';
    while (line[start] != '\0' && my_strchr(non_valid, line[start]))
        start += 1;
    while (line[start + count] != '\0'
    && !my_strchr(non_valid, line[start + count]))
        count += 1;
    my_strncpy(file, &line[start], count);
    my_memset(&line[start], ' ', count);
}

int get_input_fd(char *line)
{
    char chevrons[2] = {'<', '>'};
    char file[256];
    int fd = 0;
    int chevron = my_strchr_index(line, chevrons[0]);

    if (chevron < 0)
        return (0);
    get_file(file, line, chevron, chevrons);
    if (my_strlen(file) == 0) {
        my_putstr_error("Missing name for redirect.\n");
        return (-1);
    }
    fd = open(file, O_RDONLY);
    if (fd == -1)
        print_error(file, strerror(errno));
    return (fd);
}

int get_output_fd(char *line)
{
    char chevrons[2] = {'>', '<'};
    char file[256];
    int fd = 0;
    int chevron = my_strchr_index(line, chevrons[0]);
    int flags = O_CREAT | O_WRONLY;

    if (chevron < 0)
        return (1);
    flags |= ((line[chevron + 1] == chevrons[0]) ? (O_APPEND) : (O_TRUNC));
    get_file(file, line, chevron, chevrons);
    if (my_strlen(file) == 0) {
        my_putstr_error("Missing name for redirect.\n");
        return (-1);
    }
    fd = open(file, flags, 0644);
    if (fd == -1)
        print_error(file, strerror(errno));
    return (fd);
}