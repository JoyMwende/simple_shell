#include "shell.h"

/**
 * **strsplit - strings are splitted into words
 * @g: string
 * @x:string which is delimeter
 * Return: pointer to arrays, otherwise NULL
 */

char **strsplit(char *g, char *x)
{
	int f, l, e, r, nmwds = 0;
	char **y;

	if (g == NULL || g[0] == 0)
		return (NULL);
	if (!x)
		x = " ";

	for (f = 0; g[f] != '\0'; f++)
		if (!is_delim(g[f], x) && (is_delim(g[f + 1], x) || !g[f + 1]))
			nmwds++;

	if (nmwds == 0)
		return (NULL);

	for (f = 0, l = 0; l < nmwds; l++)
	{
		while (is_delim(g[f], x))
			f++;
		e = 0;
		while (!is_delim(g[f + e], x) && g[f + e])
			e++;
		y[l] = malloc((e + 1) * sizeof(char));
		if (!y[l])
		{
			for (e = 0; e < l; e++)
				free(y[e]);
			free(y);
			return (NULL);
		}

		for (r = 0; r < e; r++)
			y[l][r] = g[f++];
		y[l][r] = 0;
	}
	y[l] = NULL;
	return (y);
}

/**
 * **strsplit2 - does string split
 * @g: string
 *
 * @x: delimeter
 * Return: pointer to strings, otherwise NULL
 */

char **strsplit2(char *g, char x)
{
	int f, l, e, r, nmwds = 0;
	char **y;

	if (g == NULL || g[0] == 0)
		return (NULL);
	for (f = 0; g[f] != '\0'; f++)
		if ((g[f] != x && g[f + 1] == x) ||
				(g[f] != x && !g[f + 1]) || g[f + 1] == x)
			nmwds++;
	if (nmwds == 0)
		return (NULL);
	y = malloc((1 + nmwds) * sizeof(char *));
	if (!y)
		return (NULL);
	for (f = 0, l = 0; l < nmwds; l++)
	{
		while (g[f] == x && g[f] != x)
			f++;
		e = 0;
		while (g[f + e] != x && g[f + e] && g[f + e] != x)
			e++;
		y[l] = malloc((e + 1) * sizeof(char));
		if (!y[l])
		{
			for (e = 0; e < l; e++)
				free(y[e]);
			free(y);
			return (NULL);
		}
		for (r = 0; r < e; r++)
			y[l][r] = g[f++];
		y[l][r] = 0;
	}
	y[l] = NULL;
	return (y);
}
