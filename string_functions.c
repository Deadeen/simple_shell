#include "deadeenshell.h"

/**
 * _stringlen - the length of a string
 * @s: string should be checked for length
 *
 * Return: integer length of string
 */
int _stringlen(char *s)
{
	int i = 0;

	if (!s)
		return (0);

	while (*s++)
		i++;
	return (i);
}

/**
 * _strcomp - Performs lexical comparison of two strings.
 * @s1: the first string
 * @s2: the second string
 *
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int _strcomp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * start_wth - checks if needle starts with hystack
 * @hystack: string to search
 * @needle: string to find
 *
 * Return: address of next char of hystack or NULL
 */
char *start_wth(const char *hystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *hystack++)
			return (NULL);
	return ((char *)hystack);
}

/**
 * _stringcat - concatenates two strings
 * @destn: the destination buffer
 * @src: the source buffer
 *
 * Return: pointer to destination buffer
 */
char *_stringcat(char *destn, char *src)
{
	char *ret = destn;

	while (*destn)
		destn++;
	while (*src)
		*destn++ = *src++;
	*destn = *src;
	return (ret);
}
