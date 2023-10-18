#include "shell.h"

/**
 * get_environ - Returns the string array copy of environment variables.
 * @shell_info: Pointer to the shell information structure.
 * etst
 * Retturn: Array of string environment variables.
 */
char **get_environ(info_t *shell_info)
{
    /* If environment variables are not set or have changed, update them */
    if (!shell_info->environ || shell_info->env_changed)
    {
        shell_info->environ = list_to_strings(shell_info->env);
        shell_info->env_changed = 0;
    }

    return (shell_info->environ);
}

/**
 * _printenv - Prints the current environment variables.
 * @shell_info: Pointer to the shell information structure.
 * tset
 * Return: Always 0.
 */
int _printenv(info_t *shell_info)
{
    /* Print ls env val */
    print_list_str(shell_info->env);
    return (0);
}

/**
 * create_env_list - Creates a linked list of environment variables.
 * @shell_info: Pointer to the shell information structure.
 * test
 * Return: Always 0.
 */
int create_env_list(info_t *shell_info)
{
    list_t *env_node = NULL;
    size_t index;

    /* Loop env and add to ls */
    for (index = 0; environ[index]; index++)
    {
        add_node_end(&env_node, environ[index], 0);
    }

    /* Set the env ls in shell ifo stuct */
    shell_info->env = env_node;
    return (0);
}
/*done*/
