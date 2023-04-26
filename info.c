#include "shell.h"

/**
 * clear_data - initialize struct
 * @info: struct
 */

void clear_data(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->pth = NULL;
	info->argc = 0;
}

/**
 * set_data - initialize info_t
 * @info: struct addr
 * @agv: argument-vect
 */

void set_data(info_t *info, char **agv)
{
	int f = 0;

	info->fname = agv[0];
	if (info->arg)
	{
		info->argv = strsplit(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (f = 0; info->argv && info->argv[f]; f++)
			;
		info->argc = f;

		rplc_aliases(info);
		rplc_variabs(info);
	}
}

/**
 * free_data - free info_t
 * @info: struct 
 * @every: true -if freeing all fields
 */

void free_data(info_t *info, int every)
{
	ffree(info->argv);
	info->argv = NULL;
	info->pth = NULL;
	if (every)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			free_list(&(info->env));
		if (info->history)
			free_list(&(info->history));
		if (info->alias)
			free_list(&(info->alias));
		ffree(info->environ);
			info->environ = NULL;
		bfree((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}

