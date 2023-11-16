#include "deadeenshell.h"

/**
 * get_environ - returns the string array copy of our myuniver
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **get_environ(info_t *info)
{
	if (!info->myuniver || info->changecurrent)
	{
		info->myuniver = list_to_strings(info->theenv);
		info->changecurrent = 0;
	}

	return (info->myuniver);
}

/**
 * _unsetenv - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @var: the string theenv var property
 */
int _unsetenv(info_t *info, char *var)
{
	list_t *node = info->theenv;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = starts_with(node->denstr, var);
		if (p && *p == '=')
		{
			info->changecurrent = delete_node_at_index(&(info->theenv), i);
			i = 0;
			node = info->theenv;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->changecurrent);
}

/**
 * _setenv - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string theenv var property
 * @value: the string theenv var value
 *  Return: Always 0
 */
int _setenv(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = info->theenv;
	while (node)
	{
		p = starts_with(node->denstr, var);
		if (p && *p == '=')
		{
			free(node->denstr);
			node->denstr = buf;
			info->changecurrent = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->theenv), buf, 0);
	free(buf);
	info->changecurrent = 1;
	return (0);
}
