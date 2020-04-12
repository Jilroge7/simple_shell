#include "holberton.h"


char *pathchecker(char *arg)
{
	list_p *pather;
	struct stat statty;
	char *str, *pathcpy;
	int a, b, c, l, larg, strl;

	
	a = l = larg = 0;
	pather = pathlist();
	larg = _strlen(arg);

	while (pather != NULL)
	{
		l = _strlen(pather->str);
		strl = l + larg;
		str = malloc(sizeof(char) * (strl + 1));/* total argument with directory, FREE */
		if (str == NULL)
		{
			free_list(pather);
			return (NULL);
		}
		pathcpy = malloc(sizeof(char) * (l + 1));/* cpy of directory to traverse, FREE */
		if (pathcpy == NULL)
		{
			free_list(pather);
			free(str);
			return (NULL);
		}
		pathcpy = _strncpy(pathcpy, pather->str, l);
		for (b = 0; b < strl && pathcpy != '\0'; b++)
			str[b] = pathcpy[b];
		str[b] = '/';
		b++;
		for (c = 0; c < larg && arg[c] != '\0'; b++, c++)
			str[b] = pathcpy[c];
		str[b] = '\0';
		printf("String to be checked with stat: %s\n", str);
		if (stat(str, &statty) == 0)
		{
			free_list(pather);
			free(pathcpy);
			return (str);
		}
		a++;
		pather = pather->next;
		free(pathcpy);
		free(str);
	}
	free_list(pather);
	free(str);
	return (NULL);
}
int main (void)
{
	char *str = "qwerty";
	char *result = NULL;

	result = pathchecker(str);
	if (result != NULL)
		printf("Success!\n");
	else
		printf("Fail\n");
	free(result);
	/*test = pathlist();
	print_list(test);
	free_list(test);*/
	return (0);
}

list_p *pathlist(void)
{
	list_p *pathlist;
	char *path;
	char *strp;

	path = _getenv("PATH");
	strp = strtok(path, ":");
	pathlist = createpathlist(strp);
	strp = strtok(NULL, ":");
	while (strp != NULL)
	{
		
		add_node(&pathlist, strp);
		strp = strtok(NULL, ":");

	}
	return (pathlist);
}
list_p *add_node(list_p **head, char *str)
{
	list_p *tmp;
	char *newstr;
	int l;

	tmp = malloc(sizeof(list_p));
	if (tmp == NULL)
		return (NULL);
	l = _strlen(str);
	newstr = malloc(sizeof(char) * (l + 1));
	if (newstr == NULL)
	{
		free(tmp);
		return(NULL);
	}
	newstr = _strncpy(newstr, str, l);
	tmp->str = newstr;
	tmp->next = *head;
	*head = tmp;
	return (tmp);
}
list_p *createpathlist(char *str)
{
	list_p *tmp;
	char *newstr;
	int l;

	tmp = malloc(sizeof(list_p));
	if (tmp == NULL)
		return (NULL);
	l = _strlen(str);
	newstr = malloc(sizeof(char) * (l + 1));
	if (newstr == NULL)
	{
		free(tmp);
		return(NULL);
	}
	newstr = _strncpy(newstr, str, l);
	tmp->str = newstr;
	tmp->next = NULL;
	return (tmp);
}

size_t print_list(const list_p *h)
{
	int nc = 0;

	while (h != NULL)
	{
		if (h->str == NULL)
		{
			printf("[0] (nil)\n");
			h = h->next;
			nc++;
		}
		printf("%s\n", h->str);
		nc++;
		h = h->next;
	}
	return (nc);
}
void free_list(list_p *head)
{
	list_p *new;

	while (head != NULL)
	{
		new = head;
		head = head->next;
		free(new->str);
		free(new);
	}
	free(head);
}
