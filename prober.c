#include "shell.h"

/**
 * is_file_cmd - function to check if file
 * is an executable cmd
 * @info: info struct
 * @pth: file-path
 * Return: 1 if success, 0 if not
 */

int is_file_cmd(info_t *info, char *pth)
{
	struct stat st;

	(void)info;
	if (!pth || stat(pth, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dpcte_char - does char duplication
 * @pthstr: string-path
 * @strt: start
 * @stp: stop
 * Return: buf pointer
 */

char dpcte_char(char *pthstr, int strt, int stp)
{
	static char buf[1024];
	int f = 0, e = 0;

	for (e = 0, f = strt; f < stp; f++)
		if (pthstr[f] != ';')
			buf[e++] = pthstr[f];
	buf[e] = 0;
	return (buf);
}

/**
 * chk_pth - find cdm in PATH
 * @info: info struct
 * @pthstr: PATH str
 * @cmd: cmd find
 * Return: full path, else NULL
 */

char *chk_pth(info_t *info, char *pthstr, char *cmd)
{
	int f = 0, curr_pos = 0;
	char *pth;

	if (!pthstr)
		return (NULL);
	if ((strlen(cmd) > 2) && starts_with(cmd. "./"))
	{
		if (is_file_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pthstr[f] || pthstr[f] == ':')
		{
			pth = dpcte_char(pthstr, curr_pos, f);
			if (!pth)
				strcat(pth, cmd);
			else
			{
				strcat(pth, "/");
				strcat(pth, cmd);
			}
			if (is_file_cmd(info, pth))
				return (pth);
			if (!pthstr[f])
				break;
			curr_pos = f;
		}
		f++;
	}
	return (NULL);
}
