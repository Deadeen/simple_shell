#include "deadeenshell.h"

/**
 * is_cmd - determines if a file is an executable command
 * @info: the info struct
 * @direct: direct to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_cmd(info_t *info, char *direct)
{
	struct stat st;

	(void)info;
	if (!direct || stat(direct, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - duplicates characters
 * @pathstr: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (pathstr[i] != ':')
			buf[k++] = pathstr[i];
	buf[k] = 0;
	return (buf);
}

/**
 * find_path - finds this cmd in the PATH string
 * @info: the info struct
 * @pathstr: the PATH string
 * @cmd: the cmd to find
 *
 * Return: full direct of cmd if found or NULL
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *direct;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			direct = dup_chars(pathstr, curr_pos, i);
			if (!*direct)
				_strcat(direct, cmd);
			else
			{
				_strcat(direct, "/");
				_strcat(direct, cmd);
			}
			if (is_cmd(info, direct))
				return (direct);
			if (!pathstr[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}
