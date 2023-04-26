#include "shell.h"

/**
 * vfree - free a pointer and NULLS addrs
 * @pr: pointer to addrs
 * Return: 1 if free successful, else 0
 */

int vfree(void *pr)
{
	if (pr && *pr)
	{
		free(*pr);
		*pr = NULL;
		return (1);
	}
	return (0);
}
