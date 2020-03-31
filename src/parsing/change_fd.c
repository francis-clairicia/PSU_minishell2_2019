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

static int here_document_command(char const *end)
{
    char *line = NULL;
    int pipefd[2];

    if (pipe(pipefd) != 0)
        return (-1);
    while (my_putstr("? ") &&
    get_next_line(&line, 0) && my_strcmp(line, end) != 0) {
        my_putstr_fd(pipefd[1], line);
        my_putstr_fd(pipefd[1], "\n");
    }
    close(pipefd[1]);
    if (line != NULL)
        free(line);
    return (pipefd[0]);
}

int get_input_fd(char *line)
{
    char chevrons[2] = {'<', '>'};
    char file[256];
    int fd = 0;
    int chevron = my_strchr_index(line, chevrons[0]);
    bool here_document = false;

    if (chevron < 0)
        return (0);
    here_document = (line[chevron + 1] == chevrons[0]);
    get_file(file, line, chevron, chevrons);
    if (my_strlen(file) == 0) {
        my_putstr_error("Missing name for redirect.\n");
        return (-1);
    }
    if (here_document)
        return (here_document_command(file));
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