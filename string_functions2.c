#include "deadeenshell.h"

/**
 * _strcpy - copies a string
 * @dest: the destination
 * @src: the source
 *
 * Return: pointer to destination
 */
char *_strcpy(char *dest, char *src)
{
	int i = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

/**
 * _strdup - duplicates a string
 * @denstr: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *_strdup(const char *denstr)
{
	int length = 0;
	char *ret;

	if (denstr == NULL)
		return (NULL);
	while (*denstr++)
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--denstr;
	return (ret);
}

/**
 *_puts - prints an input string
 *@denstr: the string to be printed
 *
 * Return: Nothing
 */
void _puts(char *denstr)
{
	int i = 0;

	if (!denstr)
		return;
	while (denstr[i] != '\0')
	{
		_putchar(denstr[i]);
		i++;
	}
}

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	static int i;
	static char buf[SIZE_OF_BUF_WRITE];

	if (c == THE_BONEBUFF || i >= SIZE_OF_BUF_WRITE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (c != THE_BONEBUFF)
		buf[i++] = c;
	return (1);
}
