#include "shell.h"

/**
 *_putsfd - The codeblock will print the input string provided
 * @str:the placeholder forthe string to be printed
 * @fd: the placeholder for the filedescriptor that will be wirtten
 *
 * Return: the number of chars put
 */
int _putsfd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += _putfd(*str++, fd);
	}
	return (i);
}


/**
 * _eputchar -This code block will be writing the character
 * c to the stderr
 * @c: the variable to the storre The character to print
 *
 * Return:This code will return 1 On success.
 * if On error,it will return -1 is returned, and errno is set appropriately.
 */
int _eputchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * _putfd -The code block will write the characterc given to fd
 * @c:the placeholder for the charater to print
 * @fd: the placeholder for the filedescripton that will be written to
 *
 * Return:My Code will always return 1 on sucess and -1 on error
 * the errno is also set appropriately.
 */
int _putfd(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 *_eputs -This Code block will print an input string provided
 * by the user
 * @str: a variable that will be used to print the input
 *
 * Return: Nothing
 */
void _eputs(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_eputchar(str[i]);
		i++;
	}
}
