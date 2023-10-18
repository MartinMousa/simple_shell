#include "shell.h"

/**
 * add_node - Adding a node at the beginning of linked list
 * @head: address of the head node
 * @str: The content of the node
 * @num: node index that is used previously
 *
 * Return: Size of list
 */

list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *new_node;

	if (!head)
		return (NULL);
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;
	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	new_node->next = *head;
	*head = new_node;
	return (new_node);
}

/**
 * add_node_end - Adding a node to the end of the linked list
 * @head: The address of the head of the linked list
 * @str: Content of the node
 * @num: The node index used previously
 * Return: Size of the list
 */

list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *new_node, *tmp_node;

	if (!head)
		return (NULL);

	tmp_node = *head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;
	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (tmp_node)
	{
		while (tmp_node->next)
			tmp_node = tmp_node->next;
		tmp_node->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}

/**
 * print_list_str - Printing the string of a list_t linked list
 * @h: The address of the head node
 * Return: Size of the list
 */

size_t print_list_str(const list_t *h)
{
	size_t j = 0;

	while (h)
	{
		_puts(h->str ? h->str : NULL_STRING);
		_puts("\n");
		h = h->next;
		j++;
	}
	return (i);
}

/**
 * delete_node_at_index - deleting a node at certain given index
 * @head: The address of the head
 * @index: The index of node to be deleted
 * Return: 1 on success, 0 on fail
 */

int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *tmp_node, *prev_node;
	unsigned int j = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		tmp_node = *head;
		*head = (*head)->next;
		free(tmp_node->str);
		free(tmp_node);
		return (1);
	}
	tmp_node = *head;
	while (tmp_node)
	{
		if (j == index)
		{
			prev_node->next = tmp_node->next;
			free(tmp_node->str);
			free(tmp_node);
			return (1);
		}
		j++;
		prev_node = tmp_node;
		tmp_node = tmp_node->next;
	}
	return (0);
}

/**
 * free_list - freeing  all nodes of a given linked list
 * @head_ptr: The address of head node
 *
 * Return: void return
 */

void free_list(list_t **head_ptr)
{
	list_t *tmp_node, *next_node, *head_node;

	if (!head_ptr || !*head_ptr)
		return;
	head_node = *head_ptr;
	tmp_node = head_node;
	while (tmp_node)
	{
		next_node = tmp_node->next;
		free(tmp_node->str);
		free(tmp_node);
		tmp_node = next_node;
	}
	*head_ptr = NULL;
}
