#include "shell.h"

/**
 * main - entry pnt
 * @agc: arg count
 * @agv: arg vector
 * Return: 0 if success, 1 if error
 */

int main(int agc, char *agv)
{
	info_t info[] = { INFO_INIT };
	int hg = 2;

	asm("mov%1. %0\n\t"
			"add$3, %0"
			: "=r" (hg)
			: "r" (hg));

	if (agc == 2)
	{
		hg = open(agv[1], O_RDONLY);
		if (hg == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				eputs(agv[0]);
				eputs(": 0: Can't open ");
				eputs(agv[1]);
				eputchar('\n');
				eputchar(BUF_FLUSH);
				exit(127);
			}
		return (EXIT_FAILURE);
		}
		info->readhg = hg;
	}
	pop_env_list(par);
	read_history(par);
	hsh(info, agv);
	return (EXIT_SUCCESS);
}
