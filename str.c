#include "shell.h"

/**
 * strlen - return strlen
 * @y:  string
 * Return: strlen
 */

int strlen(char *y)
{
	int f = 0;

	if (!y)
		return (0);

	while (*y++)
		f++;
	return (f);
}

/**
 * strcmp - compares of two strangs.
 * @y1: 1st strang
 * @y2: 2nd strang
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */

int strcmp(char *y1, char *y2)
{
	while (*y1 && *y2)
	{
		if (*y1 != *y2)
			return (*y1 - *y2);
		y1++;
		y2++;
	}
	if (*y1 == *y2)
		return (0);
	else
		return (*y1 < *y2 ? -1 : 1);
}

/**
 * starts_with - chck if needle strts wth hstck
 * @hstck: string
 * @ndle: the substring to find
 * Return: addr of next char of hstck
 * else return NULL
 */

char *starts_with(const char *hstck, const char *ndle)
{
	while (*ndle)
		if (*ndle++ != *hstck++)
			return (NULL);
	return ((char *)hstck);
}

/**
 * strcat - concatenates two strings
 * @dstn: destination
 * @srce: source
 * Return: pointer
 */

char *strcat(char *dstn, char *srce)
{
	char *ret = dstn;

	while (*dstn)
		dstn++;
	while (*srce)
		*dstn++ = *srce++;
	*dstn = *srce;
	return (ret);
}

