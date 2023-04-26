#include "shell.h"

/**
 * hsh - main loop
 * @info: parameter
 * @agv: argument vector
 * Return: 0 if success 1 if error
 */

int hsh(info_t *info, char **agv)
{
	ssize_t s = 0;
	int inbuilt_ret = 0;

	while (s != -1 && inbuilt_ret != -2)
	{
		clear_info(info);
		if (interactive(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		s = get_input(info);
		if (s != -1)
		{
			set_info(info, agv);
			inbuilt_ret = find_builtin(info);
			if (inbuilt_ret == -1)
				find_cmd(info);
		}
		else if (interactive(info))
			_putchar('\n');
		free_info(info, 0);
	}
	write_history(info);
	free_info(info, 1);
	if (!interactive(info) && info->status)
		exit(info->status);
	if (inbuilt_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (inbuilt_ret);
}

/**
 * find_builtin - finds a builtin command
 * @info: param
 * Return: -1 if builtin isnt found,
 * 0 if builtin execution is successful,
 * 1 if builtin is found but not successful,
 * 2 if builtin-signals exit()
 */
int find_builtin(info_t *info)
{
	int f, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", exit},
		{"env", env},
		{"help", help},
		{"history", history},
		{"setenv", mysetenv},
		{"unsetenv", myunsetenv},
		{"cd", cd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (f = 0; builtintbl[f].type; f++)
		if (_strcmp(info->argv[0], builtintbl[f].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[i].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * chk_cmd - function to find command in PATH
 * @info: param
 * Return: void
 */
void chk_cmd(info_t *info)
{
	char *pth = NULL;
	int f, e;

	info->pth = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (f = 0, e = 0; info->arg[f]; f++)
		if (!delim_check(info->arg[f], " \t\n"))
			e++;
	if (!e)
		return;

	pth = chk_path(info, getenv(info, "PATH="), info->argv[0]);
	if (pth)
	{
		info->pth = pth;
		fork_file_cmd(info);
	}
	else
	{
		if ((interactive(info) || getenv(info, "PATH=")
					|| info->argv[0][0] == '/') && is_file_cmd(info, info->argv[0]))
			fork_file_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * fork_file_cmd - fork an exec thread
 * @info: param
 * Return: void
 */

void fork_file_cmd(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->pth, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}

