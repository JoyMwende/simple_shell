#include "shell.h"

/**
 * is_file_cmd - function to check if file
 * is an executable cmd
 * @par: info struct
 * @pth: file-path
 * Return: 1 if success, 0 if not
 */

int is_file_cmd(par_t *par, char *pth)
{
	struct stat st;

	(void)par;
	if (!pth || stat(pth, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dpct_char - does char duplication
 * @pthstr: string-path
 * @strt: start
 * @stp: stop
 * Return: buf pointer
 */

char dpct_char(char *pthstr, int strt, int stp)
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
 * @par: info struct
 * @pthstr: PATH str
 * @cmd: cmd find
 * Return: full path, else NULL
 */

char chk_pth(par_t *par, char *pthstr, char *cmd)
{
	int f = 0, curr_pos = 0;
	char *pth;

	if (!pthstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd. "./"))
	{
		if (is_file_cmd(par, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pthstr[f] || pthstr[f] == ':')
		{
			pth = dpcte_char(pthstr, curr_pos, f);
			if (!pth)
				_strcat(pth, cmd);
			else
			{
				_strcat(pth, "/");
				_strcat(pth, cmd);
			}
			if (is_file_cmd(par, pth))
				return (pth);
			if (!pthstr[f])
				break;
			curr_pos = f;
		}
		f++;
	}
	return (NULL);
}
