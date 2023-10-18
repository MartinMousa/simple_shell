#include "shell.h"
/**
* _strncpy - copying source to destination
* @dest: string number 1
* @src: string number 2
* @n: number of characters
* Return: The pointer to destination
*/

char *_strncpy(char *dest, char *src, int n)
{
	int j;

	for (j = 0; j < n && src[j]; j++)
		dest[j] = src[j];

	for ( ; j < n; j++)
		dest[j] = '\0';

	return (dest);
}

/**
* _strncat - concatnating two strings
* @dest: string number 1
* @src: string number 2
* @n: The number of characters
* Return: The pointer to destination
*/

char *_strncat(char *dest, char *src, int n)
{
	int length = 0, j = 0;

	while (dest[length] != '\0')
		length++;

	if (src[0])
	{
		while (src[j] != '\0' && j < n)
		{
			if (j == 0)
				dest[length] = src[0];
			else
				dest[length + j] = src[j];
			j++;
		}
	}

	return (dest);
}

/**
* _strchr - returning the address of the char in string
* @s: The string
* @c: The char that we are searching for
* Return: The char address
*/

char *_strchr(char *s, char c)
{
	int j = 0;

	while (s[j])
	{
		if (s[j] == c)
			return (&s[j]);
		j++;
	}
	if (!c)
		return (&s[j]);

	return (NULL);
}

/**
 * isDelim - checking whether the character is a delimeter
 * @c: the char that we want to check
 * @delim: the delimeter string
 * Return: 1 if true, 0 otherwise
 */

int isDelim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 * _putfd - writing a character for given fd
 * @c: The char
 * @fd: The file descriptor to write to
 *
 * Return: 1 for success, -1 for error
 */

int _putfd(char c, int fd)
{
	static int j;
	static char buffer[BUF_SIZE];

	if (c == BUF_FLUSH || j >= BUF_SIZE)
	{
		write(fd, buffer, j);
		j = 0;
	}
	if (c != BUF_FLUSH)
		buffer[j++] = c;
	return (1);
}
