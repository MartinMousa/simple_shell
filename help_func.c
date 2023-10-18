#include "shell.h"

/**
 * isInteractive - Checks if interactive mode is on.
 * @shell_info: Address of info struct.
 * test
 * 
 * Return: 1 if interactive mode, 0 otherwise.
 */
int isInteractive(info_t *shell_info)
{
    return (isatty(STDIN_FILENO) && shell_info->readfd <= STDERR_FILENO);
}

/**
 * _isalpha - Checks if a character is an alphabet character.
 * @char_to_check: Character to be checked.
 * test
 * 
 * Return: 1 if char_to_check is an alphabet character, 0 otherwise.
 */
int _isalpha(int char_to_check)
{
    return ((char_to_check >= 'a' && char_to_check <= 'z') || (char_to_check >= 'A' && char_to_check <= 'Z'));
}

/**
 * _atoi - Converts string to integer.
 * @str_to_convert: String to be converted.
 * test
 * 
 * Return: Integer value of the string.
 */
int _atoi(char *str_to_convert)
{
    unsigned int result = 0;
    int sign = 1, index = 0;

    while (str_to_convert[index] != '\0')
    {
        if (str_to_convert[index] == '-')
            sign *= -1;
        else if (str_to_convert[index] >= '0' && str_to_convert[index] <= '9')
        {
            result *= 10;
            result += (str_to_convert[index] - '0');
        }
        else if (result > 0)
            break;
        index++;
    }
    return (sign * result);
}

/**
 * _putsfd - Prints an input string to a file descriptor.
 * @str_to_print: The string to be printed.
 * @fd: The file descriptor to write to.
 * test
 * 
 * Return: Number of total characters printed.
 */
int _putsfd(char *str_to_print, int fd)
{
    int index = 0;

    if (!str_to_print)
        return (0);
    while (*str_to_print)
    {
        index += _putfd(*str_to_print++, fd);
    }
    return (index);
}

/**
 * print_d - Prints a decimal number (base 10) to a file descriptor.
 * @input_num: The input number.
 * @fd: The file descriptor to write to.
 * test
 * 
 * Return: Number of characters printed.
 */
int print_d(int input_num, int fd)
{
    int (*putchar_func)(char) = _putchar;
    int index, count = 0;
    unsigned int abs_val, current_num;

    if (fd == STDERR_FILENO)
        putchar_func = _eputchar;
    if (input_num < 0)
    {
        abs_val = -input_num;
        putchar_func('-');
        count++;
    }
    else
        abs_val = input_num;
    current_num = abs_val;
    for (index = 1000000000; index > 1; index /= 10)
    {
        if (abs_val / index)
        {
            putchar_func('0' + current_num / index);
            count++;
        }
        current_num %= index;
    }
    putchar_func('0' + current_num);
    count++;

    return (count);
}
/*done234*/
