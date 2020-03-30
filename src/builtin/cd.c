/*
** EPITECH PROJECT, 2019
** PSU_minishell1_2019
** File description:
** cd.c
*/

#include "minishell.h"

static int go_to_default_home_path(char * const *envp)
{
    int home_index = find_var_env(envp, "HOME");
    char const *home_path = NULL;

    if (home_index < 0)
        return (0);
    home_path = envp[home_index];
    home_path = &home_path[my_strchr_index(home_path, 61) + 1];
    if (chdir(home_path) < 0) {
        print_error(home_path, strerror(errno));
        return (0);
    }
    return (1);
}

static int change_working_directory(char const *arg, char * const *envp)
{
    int go_to_old_dir = !my_strcmp(arg, "-");
    char *old_pwd = get_var_value(envp, find_var_env(envp, "OLDPWD"));

    if (!go_to_old_dir && chdir(arg) < 0) {
        print_error(arg, strerror(errno));
        return (0);
    } else if (go_to_old_dir) {
        if (old_pwd == NULL) {
            print_error("", strerror(ENOENT));
            return (0);
        } else if (chdir(old_pwd) < 0) {
            print_error(old_pwd, strerror(errno));
            return (0);
        }
        my_printf("%s\n", old_pwd);
    }
    return (1);
}

int cd_builtin_command(char * const *av, char ***envp)
{
    int ac = my_array_len(av);
    char actual_dir[4097];
    char *set_old_pwd[] = {"setenv", "OLDPWD", actual_dir, NULL};
    char *set_new_pwd[] = {"setenv", "PWD", actual_dir, NULL};

    if (ac > 2) {
        print_error("cd", "Too many arguments");
        return (-1);
    }
    if (envp == NULL || getcwd(actual_dir, 4097) == NULL)
        return (-1);
    if (ac == 1 && !go_to_default_home_path(*envp))
        return (-1);
    else if (ac > 1 && !change_working_directory(av[1], *envp))
        return (-1);
    setenv_builtin_command(set_old_pwd, envp);
    getcwd(actual_dir, 4097);
    setenv_builtin_command(set_new_pwd, envp);
    return (0);
}