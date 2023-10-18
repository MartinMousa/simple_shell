#include "shell.h"

/**
 * list_len - Stating the size of linked list
 * @h: The address of the head
 * Return: The size of the linked list
 */

size_t list_len(const list_t *h)
{
	size_t j = 0;

	while (h)
	{
		h = h->next;
		j++;
	}
	return (j);
}

/**
 * list_to_strings - Converting a linked list into a string
 * @head: The address of the head
 * Return: array of strings
 */

char **list_to_strings(list_t *head)
{
	list_t *tmp_node = head;
	size_t i = list_len(head), j;
	char **string_s;
	char *str;

	if (!head || !i)
		return (NULL);
	string_s = malloc(sizeof(char *) * (i + 1));
	if (!string_s)
		return (NULL);
	for (i = 0; tmp_node; tmp_node = tmp_node->next, i++)
	{
		str = malloc(_strlen(tmp_node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(string_s[j]);
			free(string_s);
			return (NULL);
		}

		str = _strcpy(str, tmp_node->str);
		string_s[i] = str;
	}
	string_s[i] = NULL;
	return (string_s);
}


/**
 * print_list - printing all nodes of a list_t linked list
 * @h: The address of head pointer
 * Return: The size of list
 */

size_t print_list(const list_t *h)
{
	size_t j = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : NULL_STRING);
		_puts("\n");
		h = h->next;
		j++;
	}
	return (j);
}

/**
 * node_starts_with - Getting node that has string starts with prefix
 * @node: The address head
 * @prefix: Which string to match
 * @c: the next character after prefix to match
 *
 * Return: The matching node
 */

list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - gets the index of the node
 * @head: The address of the head
 * @node: The address of the node
 *
 * Return: index of node
 */

ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t j = 0;

	while (head)
	{
		if (head == node)
			return (j);
		head = head->next;
		j++;
	}
	return (-1);
}
