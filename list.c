#include "shell.h"

/**
 * add_new_node - new node at the list start
 * @head: pointer address
 * @s: str field
 * @nm: hist node index
 * Return: list size
 */

list_t *add_new_node(list_t **head, const char *s, int nm)
{
	list_t *nw_head;

	if (!head)
		return (NULL);
	nw_head = malloc(sizeof(list_t));
	if (!nw_head)
		return (NULL);
	_memset((void *)nw_head, 0, sizeof(list_t));
	nw_head->nm = nm;
	if (s)
	{
		nw_head->s = strdup(s);
		if (!nw_head->s)
		{
			free(nw_head);
			return (NULL);
		}
	}
	nw_head->next = *head;
	*head = nw_head;
	return (nw_head);
}

/**
 * add_new_node_end - add node new at end
 * @head: pointer address
 * @s: str
 * @nm: hist index node
 * Return: list size
 */

list_t *add_new_node_end(list_t **head, const char *s, int nm)
{
	list_t *nw_node, *nd;

	if (!head)
		return (NULL);

	nd = *head;
	nw_node = malloc(sizeof(list_t));
	if (!nw_node)
		return (NULL);
	_memset((void *)nw_node, 0, sizeof(list_t));
	nw_node->nm = nm;
	if (s)
	{
		nw_node->s = _strdup(s);
		if (!nw_node->s)
		{
			free(nw_node);
			return (NULL);
		}
	}
	if (nd)
	{
		while (nd->next)
			nd = nd->next;
		nd->next = nw_node;
	}
	else
		*head = nw_node;
	return (nw_node);
}

/**
 * prnt_list_s - print str element
 * @k: pointer
 * Return: list size
 */

size_t prnt_list_s(const list_t *k)
{
	size_t f = 0;

	while (k)
	{
		_puts(k->s ? k->s : "(nil)");
		_puts("\n");
		k = k->next;
		f++;
	}
	return (f);
}

/**
 * dlt_node_at_indx - delete node at certain index
 * @head: pointer address
 * @indx: node indx
 * Return: 1 if successful, 0 if not
 */

int dlt_node_at_indx(list_t **head, unsigned int indx)
{
	list_t *nd, *prior_node;
	unsigned int f = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		nd = *head;
		*head = (*head)->next;
		free(nd->s);
		free(nd);
		return (1);
	}
	nd = *head;
	while (nd)
	{
		if (f == indx)
		{
			prior_node->next = nd->next;
			free(nd->s);
			free(nd);
			return (1);
		}
		f++;
		prior_node = nd;
		nd = nd->next;
	}
	return (0);
}

/**
 * free_lst - free all list nodes
 * @hd_pntr: head node pointer address
 * Return: void
 */

void free_lst(list_t **hd_pntr)
{
	list_t *nd, nxt_nd, *head;

	if (!hd_pntr || !*hd_pntr)
		return;
	head = *hd_pntr;
	nd = head;
	while (nd)
	{
		nxt_nd = nd->next;
		free(nd->s);
		free(nd);
		nd = nxt_nd;
	}
	*hd_pntr = NULL;
}
