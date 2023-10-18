#include "shell.h"
/**
 * _strlen - returning the string length
 * @s: string (char[])
 * Return: The size of string
*/

int _strlen(char *s)
{
	int n = 0;

	while (s[n] != '\0')
		n++;
	return (n);
}

/**
* _strcmp - comparing two strings
* @s1: string number 1
* @s2: string number 2
* Return: 0 if They are equal, otherwise difference between first
* different characters
*/

int _strcmp(char *s1, char *s2)
{
	int j = 0;

	while (s1[j] != '\0')
	{
		if (s1[j] != s2[j])
			return (s1[j] - s2[j]);
		j++;
	}
	return (0);
}

/**
* _strcat - concatnating two strings
* @dest: str 1 
* @src: str 2
* Return: A pointer to target
*/

char *_strcat(char *dest, char *src)
{
	int len_int = 0, j = 1;

	while (dest[len_int] != '\0')
		len_int++;

	if (src[0])
	{
		dest[len_int] = src[0];

		while (src[j] != '\0')
		{
			dest[len_int + j] = src[j];
			j++;
		}
	}

	return (dest);

}

/**
* _strcpy - copying the string from scource to destination
* @dest: The destination string
* @src: The source string
* Return: the dest string
*/

char *_strcpy(char *dest, char *src)
{
	int j = 0;

	while (src[j] != '\0')
	{
		dest[j] = src[j];
		j++;
	}
	dest[j] = '\0';
	return (dest);
}

/**
* _strdup - duplicating a string
* @s: string
* Return: The pointer to the duplicate
*/
char *_strdup(const char *s)
{
	int length = 0;
	char *outpt;

	if (s == NULL)
		return (NULL);
	while (*s++)
		length++;

	outpt = malloc(length + 1);
	if (!outpt)
		return (NULL);

	for (length++; length--;)
		outpt[length] = *--s;
	return (outpt);

}
