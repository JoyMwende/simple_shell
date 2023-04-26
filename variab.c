#include "shell.c"

/**
 * is_buf_chain - function to test if prevailing buffer
 * character is a chain delimeter
 * @info: struct parameter
 * @bfr: buffer character
 * @d: buffer address
 * Return: 1 if buffer char is chain delimeter
 * 0 if not
 */

int is_buf_chain(info_t *info, char *bfr, size_t *d)
{
	size_t l = *d;

	if (bfr[l] == '|' && bfr[l + 1] == '|')
	{
		bfr[l] = 0;
		l++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (bfr[l] == '&' && bfr[l + 1] == '&')
	{
		bfr[l] = 0;
		l++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (bfr[l] == ';')
	{
		bfr[l] = 0;
		info->cmd_buf_typer = CMD_CHAIN;
	}
	else
	{
		return (0);
	}
	*d = l;
	return (1);
}

/**
 * chk_buf_chain - function to check if chaining
 * should progress
 * @info: struct parameter
 * @bfr: buffer character
 * @d: buffer address
 * @a: buffer start point
 * @cnt: buffer length
 * Return: void
 */

void chk_buf_chain(info_t *info, char *bfr, size_t *d, size_t a, size_t cnt)
{
	size_t l = *d;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			bfr[a] = 0;
			l = cnt;
		}
	}

	if (info->comd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			bfr[a] = 0;
			l = cnt;
		}
	}

	*d = l;
}

/**
 * rplc_aliases - function to replace tokenized string aliases
 *
 * @info: struct parameter
 * Return: 1 if rplc_aliases is successful
 * 0 if not successful
 */

int rplc_aliases(info_t *info)
{
	int f;
	list_t *nd;
	char *d;

	int f = 0;

	while (f < 10)
	{
		f++;
		nd = node_starts_with(info->alias, info->argv[0], '=')
		if (!nd)
			return (0);
		free(info->argv[0]);
		d = strchr(nd->str, '=');
		if (!d)
			return (0);
		d = strdup(d + 1);
		if (!d)
			return (0);
		par->argv[0] = d;
	}
	return (1);
}

/**
 * rplc_variabs - function to replace string variables
 * @info: struct parameter
 * Return: 1 if function successful
 * 0 if not successful
 */

int rplc_variabs(info_t *info)
{
	int f = 0;
	list_t *nd;

	for (f = 0; info->argv[f]; f++)
	{
		if (info->argv[f][0] != '$' || !info->argv[f][1])
			continue;

		if (!strcmp(info->argv[f], "$?"))
		{
			replace_string(&(info->argv[f]),
					strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[f]. "$$"))
		{
			replace_string(&(info->argv[f]),
					strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		nd = node_starts_with(info->env, &info->argv[f][1], '=');
		if (nd)
		{
			replace_string(&(info->argv[f]),
					strdup(strchr(nd->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[f], _strdup(""));
	}
	return (0);
}

/**
 * replace_string - does string replacement
 * @z: old string addr
 * @nw: new
 * Return: 1 if successful, 0 if not
 */

int replace_string(char **z, char *nw)
{
	free(*z);
	*z = nw;
	return (1);
}
