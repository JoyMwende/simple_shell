#include "shell.h"

/**
 * _memset - fills mem with constant byte
 * @y: pointer mem
 * @u: byte to fill
 * @w: amt of byte to mem
 * Return: (y) a pointer to mem
 *
 */

char _memset(char *y, char u, unsigned int w)
{
	unsigned int f;

	for (f = 0; f < w; f++)
		y[f] = u;
	return (y);
}

/**
 * dfree - function to free string
 * @xx: string of strings
 */

void dfree(char *xx)
{
	char **o = xx;

	if (!xx)
		return;
	while (*xx)
		free(*xx++);
	free(o);
}

/**
 * _realloc - reallocate mem block
 * @pr: prev pointer
 * @od_size: prev block byte size
 * @nw_size: new block byte size
 * Return: pointer
 */

void _realloc(void *pr, unsigned int od_size, unsigned int nw_size)
{
	char *d;

	if (!pr)
		return (malloc(nw_size));
	if (!nw_size)
		return (free(pr), NULL);
	if (nw_size == od_size)
		return (pr);

	d = malloc(nw_size);
	if (!d)
		return (NULL);

	od_size = od_size < nw_size ? od_size : nw_size;
	while (od_size--)
		d[od_size] = ((char *)pr)[od_size];
	free(pr);
	return (d);
}
