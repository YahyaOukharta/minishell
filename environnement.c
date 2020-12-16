#include "minishell.h"

t_env	*new_env(char *key, char *value)
{
	t_env *new;

	if (!(new = (t_env *)malloc(sizeof(t_env))))
		return (0);
	new->key = key;
	new->value = value;
	new->next = NULL;
	return (new);
}

char	*ft_key(char *s)
{
	int		i;
	char	*key;
	int		j;

	i = 0;
	j = -1;
	key = NULL;
	if (s)
	{
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

char	*ft_value(char *s)
{
	int     i;
	char    *value;

	i = 0;
	value = NULL;
	if (s)
	{
		if (!(value = ft_strdup(ft_strchr(s, '=') + 1)))
			return (NULL);
	}
	return (value);
}

void	init_environment(char **envp)
{
	int		i;
	t_env	*new;

	i = 0;
	while (envp[i] != NULL)
	{
		new = new_env(ft_key(envp[i]), ft_value(envp[i]));
		new->next = g_env;
		g_env = new;
		i++;
	}
}

void	set_env(char *key, char *value)
{
	t_env *tmp;

	if (!key || !value)
		return ;
	if (!g_env)
		return ;
	else
	{
		tmp = g_env;
		while (tmp->next && !string_equal(tmp->key, key))
			tmp = tmp->next;
		if (!tmp->next && !string_equal(tmp->key, key))
			tmp->next = new_env(key, value);
		else
		{
			free(tmp->value);
			tmp->value = ft_strdup(value);
		}
	}
}

void	unset_env(char *key)
{
	t_env *tmp;
	t_env *trash;

	tmp = g_env;
	if (!g_env)
		return ;
	if (string_equal(tmp->key, key))
		g_env = tmp->next;
	else
	{
		while (tmp->next)
		{
			if (string_equal(tmp->next->key, key))
			{
				trash = tmp->next;
				tmp->next = trash->next;
				free(trash);
				return ;
			}
			tmp = tmp->next;
		}
	}
}

t_env	*env_with_key(char *key)
{
	t_env *tmp;

	if (!g_env)
		return (0);
	tmp = g_env;
	while (tmp)
	{
		if (string_equal(tmp->key, key))
			return (tmp);
		tmp = tmp->next;
	}
	return (0);
}

int		get_env_len(void)
{
	int		i;
	t_env	*tmp;

	i = 0;
	tmp = g_env;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

char	**get_env_tab(void)
{
	char	**tab;
	t_env	*tmp;
	int		i;

	if (!g_env)
		return (0);
	if (!(tab = (char **)malloc(sizeof(char *) * (get_env_len() + 1))))
		return (0);
	i = 0;
	tmp = g_env;
	while (tmp)
	{
		tab[i] = ft_strjoin_va(3, tmp->key, "=", tmp->value);
		i++;
		tmp = tmp->next;
	}
	tab[i] = 0;
	return (tab);
}