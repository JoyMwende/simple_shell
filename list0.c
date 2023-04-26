#include "shell.h"

/**
 * linkd_lst_length - linked lists len
 * @k: pointer
 * Return: list size
 */

size_t linkd_lst_length(const list_t *k)
{
	size_t f = 0;

	while (k)
	{
		k = k->next;
		f++;
	}
	return (f);
}

/**
 * rtrn_str - return string array of list->s
 * @head: pointer
 * Return: strings array
 */

char rtrn_str(list_t *head)
{
	list_t *nd = head;
	size_t f = linkd_lst_length(head), l;
	char **gs;
	char *g;

	if (!head || !f)
		return (NULL);
	gs = malloc(sizeof(char *) * (f + 1));

	if (!gs)
		return (NULL);
	for (f = 0; nd = nd->next, f++)
	{
		g = malloc(_strlen(nd->g) + 1);
		if (!g)
		{
			for (l = 0; l < f; l++)
				free(gs[l]);
			free(gs);
			return (NULL);
		}

		g = _strcpy(g, nd->g);
		gs[f] = g;
	}
	gs[f] = NULL;
	return (gs);
}

/**
 * prt_lst - print list elements
 * @k: pointer
 * Return: lists size
 */

size_t prt_lst(const list_t *k)
{
	size_t f = 0;

	while (k)
	{
		_puts(convert_number(k->num, 10, 0));
		_putchar(';');
		_putchar(' ');
		_puts(k->g ? k->g : "(nil)");
		_puts("\n");
		k = k->next;
		f++;
	}
	return (f);
}

/**
 * nd_strt - return nde with prefix start
 * @nd: pointer
 * @prfx: string-to-match.
 * @q: next char
 * Return: match nde
 */
list_t nd_strt(list_t *nd, char *prfx, char q)
{
	char *d = NULL;

	while (nd)
	{
		d = starts_with(nd->g, prfx);
		if (d && ((q == -1) || (*d == q)))
			return (nd);
		nd = nd->next;
	}
	return (NULL);
}

/**
 * get_nd_indx - get nde indx
 * @head: pointer head
 * @nd: pointer node
 * Return: node index, else -1
 */

ssize_t get_nd_indx(list_t *head, list_t *nd)
{
	size_t f = 0;

	while (head)
	{
		if (head == nd)
			return (f);
		head = head->next;
		f++;
	}
	return (-1);
}
