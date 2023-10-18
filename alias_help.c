#include "shell.h" 
/*contains the definitions of the structures and functions used*/
/**
 * not setted alias 
 * @info: info struct
 * @name: the string alias name
 * Return: return zero for succ and 1 on any error
 * aliashelp stat
 * test1
 */

int unset_alias(info_t *info, char *name) 
/*unset an alias -  function takes two parameters: a pointer to an info_t structure and a string name*/
{
	char *x, z;
	int retted;

	x = _strchr(name, '=');
	if (!x)
		return (1);
	z = *x;
	*x = 0;
	retted = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, name, -1)));
	*x = z;
	return (retted);
}

/**
 * alais settt
 * @info: stru_for_info
 * @name: alais for the str
 * Return: give 0 succ , 1 faill
 * test2
 */

int set_alias(info_t *info, char *name)
{
	char *x;

	x = _strchr(name, '=');
	if (!x) /* alias not needed here*/
		return (1);
	if (!*++x) /* alias for the name*/
		return (unset_alias(info, name));

	unset_alias(info, name);
	return (add_node_end(&(info->alias), name, 0) == NULL); /* alias the name equal val */
}

/**
 * printal, give the value for alais
 * @node: node al
 * Return: 0 on success, 1 on error
 * test 3
 */

int print_alias(list_t *node)
{
	char *x = NULL, *v = NULL;

	if (node)
	{
		x = _strchr(node->str, '=');
		for (v = node->str; v <= x; v++)
		_putchar(*v);
		_putchar('\'');
		_puts(x + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}
/*done*/
