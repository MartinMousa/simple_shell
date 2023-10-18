#include "shell.h"
/*val env*/
/**
 * _getenv - gets the env of val
 * @info: info struct
 * @name: Env var name
 * Return: Env var value
 */

char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *o;

	while (node)
	{
		o = starts_with(node->str, name);
		if (o && *o)
			return (o);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - start or change
 * @info: info struct
 * Return: 0 on success, 1 faik
 */

int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _setenv - start or change env var
 * @info: info struct
 * @var: the variable
 * @value: the string value
 *  Return: 0 on success, 1 fail
 */

int _setenv(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *o;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = info->env;
	while (node)
	{
		o = starts_with(node->str, var);
		if (o && *o == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}

/**
 * _myremoveenv - em env variable all
 * @info: info struct
 * Return: 0 on success, 1 on efail
 * test
 * 3
 * tses
 * 6
 * 3
 */

int _myremoveenv(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		_removeenv(info, info->argv[i]);

	return (0);
}

/**
 * _removeenv - rm env variable
 * @info: info struct
 * @var: the var name
 *  Return: 1 on success, 0 err
 */

int _removeenv(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t i = 0;
	char *o;

	if (!node || !var)
		return (0);

	while (node)
	{
		o = starts_with(node->str, var);
		if (o && *o == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->env_changed);
}
/*done*/
