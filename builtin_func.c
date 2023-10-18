#include "shell.h"
/*contains the definitions of the structures and functions used*/

/**
 * _cd - dir cange
 * @info: strc info
 * Return: 0 on success, 1 on error
 * test4
 */
int _cd(info_t *info) /*change the current working directory*/
{
	char *cwd, *dir, buffer[BUF_SIZE];
	int valueretu;

	cwd = getcwd(buffer, BUF_SIZE);
	if (!cwd)
		_puts("getcwd() failed: No such file or directory\n");
	if (!info->argv[1]) /* cd no extra argv*/
	{
		/* home navigation */
		dir = _getenv(info, "HOME=");
		if (!dir) /* If no home go to PWD*/
			valueretu = chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
		else
			valueretu = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0) /* cd -for if */
	{
		/* change dir then print the new directory*/
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(cwd);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD="));
		_putchar('\n');
		valueretu = chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else /* www- var- cd */
		valueretu = chdir(info->argv[1]);
	if (valueretu == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
		return (0);
	}
	/* var env */
	_setenv(info, "OLDPWD", _getenv(info, "PWD="));
	_setenv(info, "PWD", getcwd(buffer, BUF_SIZE));
	return (0);
}

/**
 * _myexit - out shell
 * @info: info
 * Return: exit status
 */

int _myexit(info_t *info) /*out from the shell*/
{
	int cond_ext;

	if (info->argv[1])
	{
		cond_ext = _erratoi(info->argv[1]);
		if (cond_ext == -1)
		{
			info->status = 2; /* not sutable number */
			print_error(info, "Not accepted number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}

		info->nm_er = cond_ext;
		return (-2);
	}
	info->nm_er = -1; /* normal def val */
	return (-2);
}

/**
 * _history - show history ls
 * @info: info struct
 * Return: void
 */

int _history(info_t *info) /*display history ls*/
{
	print_list(info->history);
	return (0);
}

/**
 * _alias - set alias for a string cmd (_add)
 * @info: info struct
 * Return: no change 0
 */

int _alias(info_t *info) /*alias for a given string cmd*/
{
	int q = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (q = 1; info->argv[q]; q++)
	{
		p = _strchr(info->argv[q], '=');
		if (p)
			set_alias(info, info->argv[q]);
		else
			print_alias(node_starts_with(info->alias, info->argv[q], '='));
	}

	return (0);
}

/*done*/
