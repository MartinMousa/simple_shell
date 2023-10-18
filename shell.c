#include "shell.h"

/**
 * myshell - The main shell function
 * @info: info struct
 * @av: The argument vector
 *
 * Return: 0 for success or even error.
 */

int myshell(info_t *info, char **av)
{
	ssize_t v = 0;
	int builtin_ret_int = 0;

	while (v != -1 && builtin_ret_int != -2)
	{
		clear_info(info);
		if (isInteractive(info))
			_puts(INTERACTIVE_PREFIX);
		_eputchar(BUF_FLUSH);
		v = get_input(info);
		if (v != -1)
		{
			set_info(info, av);
			builtin_ret_int = find_builtin(info);
			if (builtin_ret_int == -1)
				find_cmd(info);
		}
		else if (isInteractive(info))
			_putchar('\n');
		free_info(info, 0);
	}
	free_info(info, 1);
	if (!isInteractive(info) && info->status)
		exit(info->status);
	if (builtin_ret_int == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret_int);
}

/**
 * find_builtin - finding the builtin command
 * @info: the info struct
 * Return: -1 if The builtin not found,
 *	0 if The builtin is  executed successfully,
 *	1 if The builtin found but is  not successful,
 *	2 if The builtin signals exit
 */

int find_builtin(info_t *info)
{
	int j, builtin_ret_int = -1;
	builtin_table builtintb[] = {
		{"exit", _myexit},
		{"env", _printenv},
		{"history", _history},
		{"setenv", _mysetenv},
		{"unsetenv", _myremoveenv},
		{"cd", _cd},
		{"alias", _alias},
		{NULL, NULL}
	};

	for (j = 0; builtintb[j].type; j++)
		if (_strcmp(info->argv[0], builtintb[j].type) == 0)
		{
			info->line_count++;
			builtin_ret_int = builtintb[j].func(info);
			break;
		}
	return (builtin_ret_int);
}

/**
 * find_cmd - finds a command in PATH
 * @info: the parameter & return info struct
 *
 * Return: void
 */

void find_cmd(info_t *info)
{
	char *path_ptr = NULL;
	int j, k;

	info->path_ptr = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (j = 0, k = 0; info->arg[j]; j++)
		if (!isDelim(info->arg[j], " \t\n"))
			k++;
	if (!k)
		return;

	path_ptr = parse_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path_ptr)
	{
		info->path_ptr = path_ptr;
		fork_cmd(info);
	}
	else
	{
		if ((isInteractive(info) || _getenv(info, "PATH=")
					|| info->argv[0][0] == '/') && isExe(info, info->argv[0]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * fork_cmd - forking a an exec thread so running cmd
 * @info: the info struct
 * Return: void (No thing)
 */

void fork_cmd(info_t *info)
{
	pid_t child_pid_t;

	child_pid_t = fork();
	if (child_pid_t == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid_t == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}
