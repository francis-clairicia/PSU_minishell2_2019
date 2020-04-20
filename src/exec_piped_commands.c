/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2019
** File description:
** exec_piped_commands.c
*/

#include "minishell.h"

static bool link_all_commands(command_t commands[], int nb_commands)
{
    int pipefd[2];
    int i = 0;

    for (i = 1; i < nb_commands; i += 1) {
        if (pipe(pipefd) != 0)
            return (false);
        commands[i - 1].output_fd = pipefd[1];
        commands[i].input_fd = pipefd[0];
    }
    return (true);
}

static bool init_commands(command_t commands[], char * const *piped_commands)
{
    int i = 0;
    bool status = true;

    for (i = 0; piped_commands[i] != NULL; i += 1)
        commands[i] = init_command_struct();
    for (i = 0; status == true && piped_commands[i] != NULL; i += 1) {
        commands[i] = parse_command_line(piped_commands[i]);
        status &= (commands[i].argv != NULL);
        status &= (commands[i].input_fd >= 0 && commands[i].output_fd >= 1);
    }
    return (status);
}

static void destroy_all_commands(command_t commands[], int nb_commands)
{
    int i = 0;

    for (i = 0; i < nb_commands; i += 1)
        destroy_command(&commands[i]);
}

int exec_piped_commands(char const *command_line, char ***envp)
{
    char **piped_commands = parse_input(command_line, "|", false);
    int nb_commands = my_array_len(piped_commands);
    command_t commands[nb_commands + 1];
    int status = 0;

    commands[nb_commands] = init_command_struct();
    if (status == 0 && !init_commands(commands, piped_commands))
        status = -1;
    if (status == 0 && !link_all_commands(commands, nb_commands))
        status = -1;
    if (status == 0)
        status = exec_shell_command(commands, envp);
    destroy_all_commands(commands, nb_commands);
    my_free_array(piped_commands);
    return (status);
}