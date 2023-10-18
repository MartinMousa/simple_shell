#include "shell.h"

/**
 * get_history_file - gets the history file
 * @info: info struct
 * Return: allocated string containing history file
 * file test
 */
char *get_history_file(info_t *info)
{
	char *buffer, *directory;

	directory = _getenv(info, "HOME=");
	if (!directory)
		return (NULL);
	buffer = malloc(sizeof(char) * (_strlen(directory) + _strlen(HIST_FILE) + 2));
	if (!buffer)
		return (NULL);
	buffer[0] = 0;
	_strcpy(buffer, directory);
	_strcat(buffer, "/");
	_strcat(buffer, HIST_FILE);
	return (buffer);
}

/**
 * write_history - creates a file or appends to an existing file
 * @info: info struct
 * Return: 1 on success, else -1
 * tes
 */
int write_history(info_t *info)
{
	ssize_t file_descriptor;
	char *filename = get_history_file(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	file_descriptor = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (file_descriptor == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->string, file_descriptor);
		_putfd('\n', file_descriptor);
	}
	_putfd(BUF_FLUSH, file_descriptor);
	close(file_descriptor);
	return (1);
}

/**
 * read_history - reads history from file
 * @info: the parameter struct
 *
 * Return: history count on success, 0 otherwise
 */
int read_history(info_t *info)
{
	int i, last = 0, line_count = 0;
	ssize_t file_descriptor, read_length, file_size = 0;
	struct stat st;
	char *buffer = NULL, *filename = get_history_file(info);

	if (!filename)
		return (0);

	file_descriptor = open(filename, O_RDONLY);
	free(filename);
	if (file_descriptor == -1)
		return (0);
	if (!fstat(file_descriptor, &st))
		file_size = st.st_size;
	if (file_size < 2)
		return (0);
	buffer = malloc(sizeof(char) * (file_size + 1));
	if (!buffer)
		return (0);
	read_length = read(file_descriptor, buffer, file_size);
	buffer[file_size] = 0;
	if (read_length <= 0)
		return (free(buffer), 0);
	close(file_descriptor);
	for (i = 0; i < file_size; i++)
		if (buffer[i] == '\n')
		{
			buffer[i] = 0;
			build_history_list(info, buffer + last, line_count++);
			last = i + 1;
		}
	if (last != i)
		build_history_list(info, buffer + last, line_count++);
	free(buffer);
	info->hist_count = line_count;
	while (info->hist_count-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->hist_count);
}

/**
 * build_history_list - adds entry to a history linked list
 * @info: info struct
 * @buffer: buffer
 * @line_count: the history line count, hist_count
 *
 * Return: Always 0
 */
int build_history_list(info_t *info, char *buffer, int line_count)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, buffer, line_count);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * renumber_history - fix numbers on history linked list after changes
 * @info: info struct
 * Return: The new hist_count
 */
int renumber_history(info_t *info)
{
	list_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (info->hist_count = i);
}

/*done*/
