#include "holberton.h"
/**
* _getenv - function
* @name: name of variable
*
* Description: function to get environment variable
* Return: char variable or NULL if empty
*/
char *_getenv(const char *name)
{
	char **ep = environ;
	char *np;
	int a, b;

	a = b = 0;
	while (ep[a] != NULL)
	{
		b = 0;
		np = ep[a];
		while (np[b] != '=')
			b++;
		if (strncmp(np, name, b) == 0)
		{
			while (b > 0)
			{
				np++;
				b--;
			}
			return (++np);

		}
		a++;
	}
	return (NULL);
}
/**
* strtokarray - creates an array of pointers to tokens from input string
* @str: input string
* Return: the double pointer, or NULL
*/
char **strtokarray(char *str)
{
	char **tokarray;
	char *tok;
	int c, len, t;

	c = len = t = 0;
	while (str[c] != '\0')
	{
		if (str[c + 1] == ' ' || str[c + 1] == '\0')
			t++;
		c++;
	}
	if (c == 0)
		return (NULL);
	str[strlen(str) - 1] = '\0';
	tokarray = malloc(sizeof(char *) * (t + 1));
	if (tokarray == NULL)
	{
		free(tokarray);
		return (NULL);
	}
	tok = strtok(str, " ");
	c = 0;
	while (tok != NULL)
	{
		len = strlen(tok);
		tokarray[c] = malloc(len + 1);
		if (tokarray[c] == NULL)
		{
			freeptrarray(tokarray);
			return (NULL);
		}
		strncpy(tokarray[c], tok, len + 1);
		tok = strtok(NULL, " ");
		c++;
	}
	tokarray[c] = NULL;
	return (tokarray);
}
/**
* execute_input - function
* @argv: arguments in which to execute
*
* Description: Program to exe ls -l /tmp in 5 child processes
* Return: Always 0 Success!
*/
int execute_input(char *argv[])
{
	int status, i;
	struct stat sstat;
	pid_t child;

	child = fork();
	if (child == -1)/* Fork failed */
	{
		perror("./hsh");
		exit(EXIT_FAILURE);
	}
	else if (child == 0)/* I am the child! */
	{
		if (stat(argv[0], &sstat) == 0)
			execve(argv[0], argv, NULL);
		else
		{
			perror("./hsh");
	/*              free(line);*/
			freeptrarray(argv);
			exit(EXIT_SUCCESS);
		}
	}
	else/* pid above 0, so thats ppid. wait until child ends */
	{
		waitpid(child, &status, WUNTRACED);
		/*      free(line);*/
		freeptrarray(argv);
	}
	return (0);
}
/**
* freeptrarray - frees all pointers from the array
* @ptr: pointer to pointer array
*/
void freeptrarray(char **ptr)
{
	int c = 0;

	while (ptr[c] != NULL)
		c++;

	while (c >= 0)
	{
		free(ptr[c]);
		c--;
	}
	free(ptr);
}