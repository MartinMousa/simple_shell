#include "shell.h"
/**
 * isExe - determining if a file is executable
 * @info: the info struct
 * @path: The path to the file
 *
 * Return: 1 in case of true, else 0
 */

int isExe(info_t *info, char *path)
{
	struct stat stc;

	(void)info;
	if (!path || stat(path, &stc))
		return (0);

	if (stc.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * split_path - spliting The path
 * @pathStr: the path string
 * @start: The start index
 * @stop: The stop index
 * Return: A pointer to the new buffer
 */

char *split_path(char *pathStr, int start, int stop)
{
	static char buffer[1024];
	int j = 0, k = 0;

	for (k = 0, j = start; j < stop; j++)
		if (pathStr[j] != ':')
			buffer[k++] = pathStr[j];
	buffer[k] = 0;
	return (buffer);
}

/**
 * parse_path - finding the cmd in the Path string
 * @info: the info struct
 * @pathStr: the Path string
 * @cmd: The cmd to be finded
 *
 * Return: The path of cmd if found or even NULL
 */

char *parse_path(info_t *info, char *pathStr, char *cmd)
{
	int j = 0, curr_posit = 0;
	char *path_ptr;

	if (!pathStr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (isExe(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathStr[j] || pathStr[j] == ':')
		{
			path_ptr = split_path(pathStr, curr_posit, j);
			if (!*path_ptr)
				_strcat(path_ptr, cmd);
			else
			{
				_strcat(path_ptr, "/");
				_strcat(path_ptr, cmd);
			}
			if (isExe(info, path_ptr))
				return (path_ptr);
			if (!pathStr[j])
				break;
			curr_posit = j;
		}
		j++;
	}
	return (NULL);
}
