#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

typedef struct s_node{
	int number;
	char *key;
	char *value;
	struct s_node *next;
	struct s_node *prev;
} t_node;


char	**ft_split(char const *s, char c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *s);

void commit(t_node *head, char *key, char *value);
void restore(t_node *head, int n);
void print(t_node *list);
void push(t_node *head);