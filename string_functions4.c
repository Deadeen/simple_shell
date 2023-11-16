#include "deadeenshell.h"

/**
 * **strtow - splits a string into words. Repeat delimiters are ignored
 * @denstr: the input string
 * @d: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **strtow(char *denstr, char *d)
{
	int i, j, k, m, numwords = 0;
	char **s;

	if (denstr == NULL || denstr[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (i = 0; denstr[i] != '\0'; i++)
		if (!is_delim(denstr[i], d) && (is_delim(denstr[i + 1], d) || !denstr[i + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (is_delim(denstr[i], d))
			i++;
		k = 0;
		while (!is_delim(denstr[i + k], d) && denstr[i + k])
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = denstr[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}

/**
 * **strtow2 - splits a string into words
 * @denstr: the input string
 * @d: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtow2(char *denstr, char d)
{
	int i, j, k, m, numwords = 0;
	char **s;

	if (denstr == NULL || denstr[0] == 0)
		return (NULL);
	for (i = 0; denstr[i] != '\0'; i++)
		if ((denstr[i] != d && denstr[i + 1] == d) ||
		    (denstr[i] != d && !denstr[i + 1]) || denstr[i + 1] == d)
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (denstr[i] == d && denstr[i] != d)
			i++;
		k = 0;
		while (denstr[i + k] != d && denstr[i + k] && denstr[i + k] != d)
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = denstr[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}
