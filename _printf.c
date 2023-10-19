#include "main.h"  

typedef struct specifiers
{
    char specifier;
    int (*function)(va_list);
} specifiers;

int print_integer(va_list args)
{
    int n = va_arg(args, int);
    int num = n, i = 0, len = 0;
    char s[10];  /* assuming max 10 digits for int */

    if (n == 0)
    {
        write(1, "0", 1);
        return (1);
    }
    if (n < 0)
    {
        n = -n;
        write(1, "-", 1);
        len++;
    }
    while (num)
    {
        s[i++] = (num % 10) + '0';
        num /= 10;
    }
    while (i--)
    {
        write(1, &s[i], 1);
        len++;
    }
    return (len);
}

int (*get_function(char s))(va_list)
{
    int i = 0;

    specifiers spec[] = {
        {'c', print_char},
        {'s', print_string},
        {'%', print_percent},
        {'i', print_integer},
        {'d', print_integer},
        {'\0', NULL}
    };

    while (spec[i].specifier)
    {
        if (spec[i].specifier == s)
            return (spec[i].function);
        i++;
    }
    return (NULL);
}

