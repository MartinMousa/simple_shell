#include "shell.h"

/**
 * convert_number - Converter function with base (itoa).
 * @input_num: Number to be converted.
 * @base: Base for conversion.
 * @flags: Argument flags.
 *
 * Return: Converted string.
 */
char *convert_number(long int input_num, int base, int flags)
{
    static char *digit_array;
    static char buffer[50];
    char sign = 0;
    char *ptr;
    unsigned long num = input_num;

    /*  num negv- and not unsigned, change to  posit and set the sign */
    if (!(flags & CONVERT_UNSIGNED) && input_num < 0)
    {
        num = -input_num;
        sign = '-';
    }

    /* digit arr */
    digit_array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";

    /* Start end buffer */
    ptr = &buffer[49];
    *ptr = '\0';

    /* Convert the numbere */
    do
    {
        *--ptr = digit_array[num % base];
        num /= base;
    } while (num != 0);

    /* If sign, add to number */
    if (sign)
        *--ptr = sign;

    return (ptr);
}

/**
 * remove_comments - Removes comments starting with '#' from a string.
 * @str: Address of the string to modify.
 * test
 * 
 * Return: Nothing.
 */
void remove_comments(char *str)
{
    int index;

    /* Loop string and replace '#' with '\0' if it's a comment */
    for (index = 0; str[index] != '\0'; index++)
        if (str[index] == '#' && (!index || str[index - 1] == ' '))
        {
            str[index] = '\0';
            break;
        }
}
/*doens*/
