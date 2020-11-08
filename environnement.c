#include "minishell.h"

t_env   *new_env(char *key, char *value)
{
	t_env *new;

	new = (t_env *)malloc(sizeof(t_env));
	new->key = key;
	new->value = value;
	new->next = NULL;
	return (new);
}

char        *ft_key(char *s)
{
	int     i;
	char    *key;
	int     j;

	i = 0;
	j = -1;
	key = NULL;
	if (s)
	{
		/*
			We need To check Fot The First '='  in s 
			export ha=ha=ha
			e1r5p12% env | grep ha 
			ha=ha=ha
			e1r5p12% echo $ha
			ha=ha
		*/
		while (s[i] != '\0' && s[i] != '=')
			i++;
		if (!(key = (char *)malloc(sizeof(char ) * (i + 1))))
			return (NULL);
		while (++j < i)
			key[j] = s[j];
		key[j] = '\0';    
	}
	return (key);
}

char        *ft_value(char *s)
{
	int     i;
	char    *value;

	i = 0;
	value = NULL;
	if (s)
	{
		/*
			3gzt nzid Function it would be better if we had a 
			struct for key, value inside our linked list 
		*/
		if (!(value = ft_strdup(ft_strchr(s, '=') + 1)))
			return (NULL);
	}
	return (value);
}

void        init_environment(char **envp)
{
	int     i;
	t_env   *new;

	i = 0;
	while (envp[i] != NULL)
	{
		new = new_env(ft_key(envp[i]), ft_value(envp[i]));
		new->next = g_env;
		g_env = new;
		i++;
	}
	// while (g_env != NULL)
	// {
	// 	ft_printf("%s | %s\n", g_env->key, g_env->value);
	// 	g_env = g_env->next;
	// }
}
