#include "shell.h"
/**
* _memset - filling the first n bytes of the memory region
* pointed to by s with the constant byte b
* @s: the starting address
* @b: the byte per address
* @n: The num of elements to fill with data
* Return: A pointer to the starting position on the memory
*/

char *_memset(char *s, char b, unsigned int n)
{
	unsigned int j;

	for (j = 0; j < n; j++)
		*(s + j) = b;

	return (s);
}

/**
* _realloc - reallocating a memory block
* @ptr: The adress of the prev block
* @old_size: The size of the allocated space for the pointer
* @new_size: The new size
* Return: A pointer to new block
*/

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *res_ptr;
	unsigned int j;

	if (new_size == old_size)
		return (ptr);

	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}

	if (ptr == NULL)
	{
		res_ptr = malloc(new_size);
		if (!res_ptr)
			return (NULL);
		return (res_ptr);
	}

	res_ptr = malloc(new_size);
	if (!res_ptr)
		return (NULL);

	for (j = 0; j < old_size && j < new_size; j++)
		res_ptr[j] = ((char *)ptr)[j];

	free(ptr);
	return (res_ptr);
}

/**
 * ffree - freeing an array of string
 * @pstr: An array of strings
 * Return: void (Nothing)
 */

void ffree(char **pstr)
{
	char **x = pstr;

	if (!pstr)
		return;
	while (*pstr)
		free(*pstr++);
	free(x);
}

/**
 * bfree - freeing a pointer and NULLs the address
 * @addr: The address of the poninter that need to be free
 * Return: 1 on success, 0 fail
 */

int bfree(void **addr)
{
	if (addr && *addr)
	{
		free(*addr);
		*addr = NULL;
		return (1);
	}
	return (0);
}
