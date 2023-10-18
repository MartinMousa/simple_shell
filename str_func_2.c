#include "shell.h"
/**
 * starts_with - checking if string starts with a certain string
 * @s1: string to search in
 * @s2: substring to search for
 *
 * Return: The address of the next char of main str
*/

char *starts_with(const char *s1, const char *s2)
{
	while (*s2)
		if (*s2++ != *s1++)
			return (NULL);
	return ((char *)s1);
}

/**
 * _puts - printing the  string
 * @str: string to be printed (char[])
 * Return: void (Nothing)
*/

void _puts(char *str)
{
	int k = 0;

	if (!str)
		return;

	while (str[k] != '\0')
	{
		_putchar(str[k]);
		k++;
	}
}

/**
 * _putchar - printing a character to stdout
 * @c: char
 *
 * Return: 1 for success, -1 for error
 */
int _putchar(char c)
{
	static int j;
	static char buffer[BUF_SIZE];

	if (c == BUF_FLUSH || i >= BUF_SIZE)
	{
		write(STDOUT_FILENO, buffer, j);
		j = 0;
	}

	if (c != BUF_FLUSH)
		buffer[j++] = c;
	return (1);
}

/**
 * **strtow - splitting a string into separate words
 * @str: String
 * @d: the dilimeter string
 * Return: The pointer to array of words
 */

char **strtow(char *str, char *d)
{
	int i, j, k, l, num_words = 0;
	char **sk;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";

	for (i = 0; str[i] != '\0'; i++)
		if (!isDelim(str[i], d) && (isDelim(str[i + 1], d) || !str[i + 1]))
			num_words++;

	if (num_words == 0)
		return (NULL);
	sk = malloc((1 + num_words) * sizeof(char *));
	if (!sk)
		return (NULL);
	for (i = 0, j = 0; j < num_words; j++)
	{
		while (isDelim(str[i], d))
			i++;
		k = 0;
		while (!isDelim(str[i + k], d) && str[i + k])
			k++;
		sk[j] = malloc((k + 1) * sizeof(char));
		if (!sk[j])
		{
			for (k = 0; k < j; k++)
				free(sk[k]);
			free(sk);
			return (NULL);
		}
		for (l = 0; l < k; l++)
			sk[j][l] = str[i++];
		sk[j][l] = 0;
	}
	sk[j] = NULL;
	return (sk);
}

/**
 * **strtow2 - splitting the string into separate words
 * @str: string
 * @d: the delimeter char
 * Return: The pointer to array of words
 */

char **strtow2(char *str, char d)
{
	int i, j, k, m, num_words = 0;
	char **sk;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != d && str[i + 1] == d) ||
				    (str[i] != d && !str[i + 1]) || str[i + 1] == d)
			num_words++;
	if (num_words == 0)
		return (NULL);
	sk = malloc((1 + num_words) * sizeof(char *));
	if (!sk)
		return (NULL);
	for (i = 0, j = 0; j < num_words; j++)
	{
		while (str[i] == d && str[i] != d)
			i++;
		k = 0;
		while (str[i + k] != d && str[i + k] && str[i + k] != d)
			k++;
		sk[j] = malloc((k + 1) * sizeof(char));
		if (!sk[j])
		{
			for (k = 0; k < j; k++)
				free(sk[k]);
			free(sk);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			sk[j][m] = str[i++];
		sk[j][m] = 0;
	}
	sk[j] = NULL;
	return (sk);
}
