#include "shell.h"

/**
 * read_buf - reading the buffer
 * @info: info struct
 * @buf: The buffer
 * @size: THe new size
 *
 * Return: The size of read bytes
 */

ssize_t read_buf(info_t *info, char *buf, size_t *size)
{
	ssize_t l = 0;

	if (*size)
		return (0);

	l = read(info->readfd, buf, BUF_SIZE);

	if (l >= 0)
		*size = l;
	return (l);
}

/**
 * _getline - getting the input line from STDIN
 * @info: info struct
 * @pBuf: The address of pointer to buffer
 * @length: The length of Buffer
 *
 * Return: The actual number of bytes read
 */

int _getline(info_t *info, char **pBuf, size_t *length)
{
	static char buffer[BUF_SIZE];
	static size_t j, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *pBuf;
	if (p && length)
		s = *length;
	if (j == len)
		j = len = 0;

	r = read_buf(info, buffer, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buffer + j, '\n');
	k = c ? 1 + (unsigned int)(c - buffer) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buffer + j, k - j);
	else
		_strncpy(new_p, buffer + j, k - j + 1);

	s += k - i;
	j = k;
	p = new_p;

	if (length)
		*length = s;
	*pBuf = p;
	return (s);
}

/**
 * input_buf - The buffers chained commands
 * @info: info struct
 * @buf: The buffer address
 * @len: The size address
 *
 * Return: The number of read bytes
 */

ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t v = 0;
	size_t len_pt = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
		v = _getline(info, buf, &len_pt);
		if (v > 0)
		{
			if ((*buf)[v - 1] == '\n')
			{
				(*buf)[v - 1] = '\0';
				v--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			{
				*len = v;
				info->cmd_buf = buf;
			}
		}
	}
	return (v);
}

/**
 * sigintHandler - handling ctrl-C
 * @sig_num: the signal number
 * Return: void (No thing)
 */

void sigintHandler(int sig_num)
{
	_puts("\n");
	_puts(INTERACTIVE_PREFIX);
	_putchar(BUF_FLUSH);
	(void) sig_num;
}

/**
 * get_input - getting a line of input
 * @info: info struct
 * Return: The num of read bytes
 */

ssize_t get_input(info_t *info)
{
	static char *buffer;
	static size_t i, j, len;
	ssize_t v = 0;
	char **buf_pt = &(info->arg), *pt;

	_putchar(BUF_FLUSH);
	v = input_buf(info, &buffer, &len);
	if (v == -1)
		return (-1);
	if (len) /* we there is commands left in the chain buffer */
	{
		j = i;
		pt = buffer + i;
		check_chain(info, buffer, &j, i, len);
		while (j < len)
		{
			if (isChain(info, buffer, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			info->cmd_buf_type = CMD_DEFAULT;
		}

		*buf_pt = pt;
		return (_strlen(pt));
	}

	*buf_pt = buffer;
	return (v);
}
