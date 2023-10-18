#include "shell.h"

/**
 * isChain - ?? current char is chain of deli
 * @info: para strc
 * @buf: char buff
 * @p: address of curr position in buf
 * Return: 1 if chain delimeter, 0 otherwise
 * test3
 */

int isChain(info_t *info, char *buf, size_t *p)
{
	size_t t = *p;

	if (buf[t] == '|' && buf[t + 1] == '|')
	{
		buf[t] = 0;
		t++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[t] == '&' && buf[t + 1] == '&')
	{
		buf[t] = 0;
		t++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[t] == ';')
	{
		buf[t] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = t;
	return (1);
}

/**
 * check_chain - checks if should continue chaining or not based on prev cmd
 * @info: para strc
 * @buf: buff char
 * @p: address of current position in buf
 * @i: starting position in buf
 * @len: length of buf
 * Return: void
 */

void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t t = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		/* if && must succ first*/
		if (info->status)
		{
			buf[i] = 0;
			t = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		/* if not \\ */
		if (!info->status)
		{
			buf[i] = 0;
			t = len;
		}
	}

	*p = t;
}
/*done*/
