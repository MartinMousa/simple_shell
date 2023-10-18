#include "shell.h"

/**
 * _eputs - Prints an input string to stderr.
 * @input_str: The string to be printed.
 *trass
 * Return: Nothing.
 */
void _eputs(char *input_str)
{
    int index = 0;

    /* str null, return */
    if (!input_str)
        return;

    /* Loop str and print evry char */
    while (input_str[index] != '\0')
    {
        _eputchar(input_str[index]);
        index++;
    }
}

/**
 * _eputchar - Writes the character c to stderr.
 * @char_to_print: The character to print.
 *
 * Return: On success 1. On error, -1.
 */
int _eputchar(char char_to_print)
{
    static int buffer_index;
    static char buffer[BUF_SIZE];

    /* char buffer flush or full, write buffer to stderr and reset */
    if (char_to_print == BUF_FLUSH || buffer_index >= BUF_SIZE)
    {
        write(STDERR_FILENO, buffer, buffer_index);
        buffer_index = 0;
    }

    /* char is not buffer flush, add it to the buffer */
    if (char_to_print != BUF_FLUSH)
        buffer[buffer_index++] = char_to_print;

    return (1);
}

/**
 * _erratoi - Converts a string to an integer.
 * @str_to_convert: The string to be converted.
 *
 * Return: 0 if no numbers in string, otherwise num or -1 on error.
 */
int _erratoi(char *str_to_convert)
{
    int index = 0;
    unsigned long int result = 0;

    /* str = '+', skip */
    if (*str_to_convert == '+')
        str_to_convert++;

    /* Loop str change dig to int */
    for (index = 0;  str_to_convert[index] != '\0'; index++)
    {
        if (str_to_convert[index] >= '0' && str_to_convert[index] <= '9')
        {
            result *= 10;
            result += (str_to_convert[index] - '0');
            if (result > INT_MAX)
                return (-1);
        }
        else
            return (-1);
    }
    return (result);
}

/**
 * print_error - Prints an error message.
 * @shell_info: Address of info struct.
 * @error_str: Error string.
 *
 * Return: void.
 */
void print_error(info_t *shell_info, char *error_str)
{
    _eputs(shell_info->fname);
    _eputs(": ");
    print_d(shell_info->line_count, STDERR_FILENO);
    _eputs(": ");
    _eputs(shell_info->argv[0]);
    _eputs(": ");
    _eputs(error_str);
}

/*done*/
