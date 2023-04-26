#include "shell.h"

/**
 * strcpy - copy string
 * @dstn: destination
 * @srce: source
 * Return: pointer to dstn
 */

char *strcpy(char *dstn, char *srce)
{
	int f = 0;

	if (dstn == srce || srce == 0)
		return (dstn);
	while (srce[f])
	{
		dstn[f] = srce[f];
		f++;
	}
	dstn[f] = 0;
	return (dstn);
}

/**
 * strdup - duplicate string
 * @g: string
 * Return: pointer to str
 */
char *strdup(const char *g)
{
	int count = 0;
	char *ret;

	if (g == NULL)
		return (NULL);
	while (*g++)
		count++;
	ret = malloc(sizeof(char) * (count + 1));
	if (!ret)
		return (NULL);
	for (count++; count--;)
		ret[count] = *--g;
	return (ret);
}

/**
 * puts - prints str
 * @g: string
 * Return: Nothing
 */
void puts(char *g)
{
	int f = 0;

	if (!g)
		return;
	while (g[f] != '\0')
	{
		_putchar(f[f]);
		f++;
	}
}

/**
 * _putchar - write char c to stdout
 * @c: The char
 * Return: On success 1.
 * On error, -1, and set errno appropriately.
 */

int _putchar(char c)
{
	static int f;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buf, f);
		f = 0;
	}
	if (c != BUF_FLUSH)
		buf[f++] = c;
	return (1);
}
