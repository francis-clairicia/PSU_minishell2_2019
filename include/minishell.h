/*
** EPITECH PROJECT, 2019
** PSU_minishell1_2019
** File description:
** minishell.h
*/

#ifndef HEADER_MINI_SHELL
#define HEADER_MINI_SHELL

#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include "my.h"
#include "mylist.h"

int kill(pid_t pid, int sig);

typedef __sighandler_t sighandler_t;

#define DEFAULT_ENVIRONMENT __environ

#ifndef WCOREDUMP
#define WCOREDUMP(wstatus) __WCOREDUMP(wstatus)
#endif

enum SIGINT_HANDLER_FUNCTION
{
    PROMPT,
    PROCESS
};

typedef struct command_line
{
    char **argv;
    int input_fd;
    int output_fd;
    int error_fd;
} command_t;

int mysh(void);
int minishell(char const *command_line, char ***envp);
int exec_shell_commands(command_t commands[], char ***envp);
int exec_piped_commands(char const *command_line, char ***envp);
void print_command_prompt(char const *cwd, char * const *envp);
char *get_path_to_executable(char const *binary, char * const *envp);
char *join_path(char const *path_1, char const *path_2);
char *find_binary_in_path(char const *binary, char * const *envp);
int find_var_env(char * const *envp, char const *var);
char *get_var_value(char * const *envp, int index);
char *create_variable(char const *variable, char const *value);

char **parse_input(char const *input, char const separators[], bool remove);
command_t init_command_struct(void);
void destroy_command(command_t *command);
command_t parse_command_line(char const *command_line);
int get_input_fd(char *line);
int get_output_fd(char *line);
int get_character_index(char const *line, char character);
bool check_redirection_validity(char const *line);

typedef int (*builtin_t)(char * const *av, char ***envp);

struct builtin
{
    char const *command;
    builtin_t function;
};

int launch_builtin(builtin_t builtin, command_t commands[], char ***envp);
builtin_t is_builtin(char * const *cmd);
int cd_builtin_command(char * const *av, char ***envp);
int env_builtin_command(char * const *av, char ***envp);
int exit_builtin_command(char * const *av, char ***envp);
int setenv_builtin_command(char * const *av, char ***envp);
int unsetenv_builtin_command( char * const *av, char ***envp);

sighandler_t bind_sigint_signal(int func);
void sigint_handler_for_prompt(int signum);
void sigint_handler_for_process(int signum);

void print_error(char const *filepath, char const *error);
void print_signal(int signum, int core_dump);
char *error_exec(int errnum);

#endif