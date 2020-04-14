#ifndef HOLBERTON_H
#define HOLBERTON_H
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
void _printppid(void);
int _putchar(char c);
char *read_input(void);/* was char *s)*/
char **strtokarray(char *str);
void freeptrarray(char **ptr);
char *_strncpy(char *dest, char *src, int n);
int _strlen(char *s);
int _strncmp(const char* s1, const char* s2, size_t n);
int execute_input(char *argv[]);
char *_getenv(const char *name);
extern char **environ;
typedef struct pathlist
{
	char *str;
	struct pathlist *next;
} list_p;
list_p *add_node(list_p **head, char *str);
list_p *createpathlist(char *str);
size_t print_list(const list_p *h);
void free_list(list_p *head);
list_p *pathlist(void);
#endif /*HOLBERTON_H*/
