#include "minishell.h"

int			check_arg(char *s)
{
	int i;

	i = 0;
	if (s)
	{
		while (s[i] != '\0')
		{
			if (s[i] == ' ')
				i++;
			if (ft_isalnum(s[i]))
				return (0);
			i++;
		}
	}
	return (1);
}

typedef     struct s_redir
{
    int to_fd;
	int cc_fd;
	int from_fd;
}                  t_redir;

int			check_redir(char *s)
{
	t_redir	dir;
	int		i;

	dir.to_fd = 0;
	dir.cc_fd = 0;
	dir.from_fd = 0;
	i = 0;
	if (ft_strchr(s, '>') && !ft_strnstr(s, ">>", ft_strlen(s)))
	{
		dir.to_fd = 1;
		if (check_arg(ft_strchr(s, '>') + 1))
			return (1);
	}
	else if (ft_strchr(s, '<'))
	{
		dir.from_fd = 1;
		if (check_arg(ft_strchr(s, '<')))
			return (1);
	}
	else if (ft_strnstr(s, ">>", ft_strlen(s)) != NULL)
		dir.cc_fd = 1;
	if (ft_strchr(s, '>') || ft_strchr(s, '<') || ft_strnstr(s, ">>", ft_strlen(s)))
	{
		if (dir.to_fd)
			return (check_redir(ft_strchr(s, '>') + 1));
		else if (dir.from_fd)
			return (check_redir(ft_strchr(s, '<') + 1));
		else
			return (check_redir(ft_strnstr(s, ">>", ft_strlen(s)) + 1));
	}
	return (0);
}

int     ft_have_end(char *s, char c, int *pos)
{
    (*pos)++;
    while (s[*pos] != '\0')
    {
        if (s[*pos] == c)
            return (true);
        (*pos)++;
    }
    return (false);
}

int     ft_need_data(char *s, int *pos)
{

    char    c;

    while (s[*pos] != '\0' && !QUOTE(s[*pos]))
        (*pos)++;
    while (s[*pos] != '\0' && QUOTE(s[*pos]))
    {
        c = s[*pos];
        if (ft_have_end(s, c, pos))
            return (false);
    }
    return (true);
}

int     has_quotes(char *s)
{
    int  i;

    i  = 0;
    if (s)
    {
        while (s[i] != '\0')
        {
            if (QUOTE(s[i]))
                return (1);
            i++;
        }
    }
    return (0);
}

char    *ft_check_quotes(char *s)
{
    int     i;
    char    *data;
    char    *tmp;
    int     nd_data;

    i = 0;
    tmp = ft_strdup(s);
    while (has_quotes(tmp + i) && s[i] != '\0')
    {
        if ((nd_data = ft_need_data(tmp, &i)))
        {
            ft_prompt(">", &data);
            tmp = ft_strjoin(tmp, data);
            tmp = ft_check_quotes(tmp);
        }
        i++;
    }
    return (tmp);
}

char		*complete_pipe(char *s)
{
	char *line;

	ft_prompt("pipe> ", &line);
	return (ft_strjoin(s, line));
}

int			check_str(char *s)
{
	int i;

	i = 0;
	while (s[i] != '\0')
	{
		if (ft_isalnum(s[i]))
			return (1);
		i++;
	}
	return (0);
}

int			ft_cnt_pipe(char **s)
{
	int i;
	int cnt;

	i = 0;
	cnt = 0;
	while (s[i] != NULL)
	{
		if (check_str(s[i]))
			cnt++;
		i++;
	}
	return (cnt);
}

char		*check_pipe(char *s)
{
	int i;
	int cnt;
	char **l;
	char	*cmp;
	i = 0;
	cnt = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '|' && s[i + 1] != '|')
			cnt++;
		else if (s[i] == '|' && s[i + 1] == '|')
			return (NULL);
		i++;
	}
	if (!(l = ft_split(s, '|')))
		return (NULL);
	if (!(cnt == ft_cnt_pipe(l) - 1) && ft_cnt_pipe(l) != 0)
	{
		if (!(cmp = complete_pipe(s)))
			return (NULL);
		cmp = check_pipe(cmp);
	}
	if ((ft_cnt_pipe(l) == 0) && cnt == 1)
		return (NULL);
	return (cmp);
}

char        *check_syntax(char *s)
{
	char    *line;

	line = ft_strdup(s);
	if (ft_strchr(s, '\'') || ft_strchr(s, '\"'))
	{
		free(line);
		line = ft_check_quotes(s);
	}
	if (ft_strchr(s, '>') || ft_strchr(s, '<') || ft_strnstr(s, ">>", ft_strlen(s)))
	{
		if (check_redir(s))
		{
            free(line);
            ft_putstr_fd("redirections Syntax error !!\n", 1);
            return (NULL);
        }
		
	}
	// maybe later 
	if (ft_strchr(s, '|'))
	{
		if (!(check_pipe(s)))
		{
            free(line);
			ft_putstr_fd("Parse Error near |\n", STDOUT);
			return (NULL);
		}
	}
	// if (env_var)
	// t_cmd	shell;
	// if (!(shell.cmds = ft_split(s, ';'))
	// 	//////free_g();
	return (line);
}