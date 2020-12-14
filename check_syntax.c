#include "minishell.h"


int			have_end(char *s, char quote, int *start)
{
	while (*start < (int )ft_strlen(s))
	{
		if (s[*start] == quote)
		{
			*start += 1;
			return (1);
		}
		*start += 1;
	}
	return (0);
}

int			check_quotes(char	*s, int *pos)
{
	int 	i;
	int 	start;
	int		end;
	char	quote;

	i = 0;
	start = 0;
	end = ft_strlen(s);
	quote = '0';
	while (start < end)
	{
		if (s[start] == '\'' || s[start] == '\"')
		{
			*pos = start;
			quote = s[start++];
			if (have_end(s, quote, &start) == 0)
				return (0);
		}
		start++;
	}
	return (1);
}

int			check_pipe(char *s)
{
	char **pipes;
	int i;
	int	nb_pipes;

	i = 0;
	nb_pipes = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '|' && s[i + 1] != '|')
			nb_pipes++;
		else if (s[i] == '|' && s[i + 1] == '|')
			return (0);
		i++;
	}
	pipes = ft_split(s, '|');
	i = tab_len(pipes);
	if (nb_pipes == i - 1)
		return (1);
	return (0);
}

int			check_arg(char *s)
{
	int i;
	int	end;
	int in;

	i = 0;
	in = 0;
	end = 0;
	if (s)
	{
		while (!(s[i] == '>' || s[i] == '<' || ft_strncmp(s, ">>", ft_strlen(s) < 3 ? 3 : ft_strlen(s)) == 0) && in == 0)
			i++;
		if ((s[i] == '>' || s[i] == '<' || ft_strncmp(s, ">>", ft_strlen(s) < 3 ? 3 : ft_strlen(s)) == 0) && in == 0)
		{
			if (s[i] == '>' && s[i + 1] == '>')
				i += 2;
			else if (s[i] == '<')
				i += 1;
			else
				i++;
		}
		while (s[i] != '\0')
		{
			if (QUOTE(s[i]) && in == 0)
			{
				end = i + 1;
				if (inside_quotes(s + i + 1, &end, s[i]))
					in = 1;
			}
			if (i == end)
				in = 0;
			while (s[i] == ' ' && in == 0)
				i++;
			if ((ft_isalpha(s[i]) || ft_isdigit(s[i])))
				return (0);
			if ((s[i] == '>' || s[i] == '<' || ft_strncmp(s, ">>", ft_strlen(s) < 3 ? 3 : ft_strlen(s)) == 0) && in == 0)
				return (1);
			if (s[i] != '\0')
				i++;
		}
	}
	return (1);
}

int		 ft_strsearch(char *s, char n)
{
	int 	i;
	int		in;
	int		end;

	i = 0;
	in = 0;
	end = 0;
	if (s)
	{
		while (s[i] != '\0')
		{
			if (QUOTE(s[i]) && in == 0)
			{
				end = i + 1;
				if (inside_quotes(s + i + 1, &end, s[i]))
					in = 1;
			}
			if (i == end)
				in = 0;
			if (s[i] == n && in == 0)
				return (1);
			i++;
		}
	}
	return (0);
}

int			has_redir(char *s, int *pos)
{
	if (s)
	{
		int 	i;
		int		in;
		int		end;

		i = 0;
		in = 0;
		end = 0;
		while (s[i] != '\0')
		{
			if (QUOTE(s[i]) && in == 0)
			{
				end = i + 1;
				if (inside_quotes(s + i + 1, &end, s[i]))
					in = 1;
			}
			if (i == end)
				in = 0;
			if ((s[i] == '>' || s[i] == '<' || ft_strncmp(s, ">>", ft_strlen(s) < 3 ? 3 : ft_strlen(s)) == 0) && in == 0)
			{
				*pos += i;
				return (1);
			}
			i++;
		}
	}
	else
		return (1);
	return (0);
}

int			check_redir(char *s)
{
	int i;

	i = 0;
	/*** Error Handling Sucks ***\     -/-*-]*/
	while (has_redir(s + i, &i) == 1 && s[i] != '\0')
	{
		if (ft_strsearch(s + i, '>') && !ft_strnstr(s, ">>", ft_strlen(s)))
		{
			ft_printf("Checking0 %s\n", ft_strchr(s + i, '>') + 1);
			if (check_arg(s + i))
				return (0);
		}
		if (ft_strsearch(s + i, '<') && !ft_strnstr(s + i, "<<", ft_strlen(s)))
		{
			ft_printf("Checking1 %s\n", ft_strchr(s + i, '<'));
			if (check_arg(s + i))
				return (0);
		}
		if (ft_strnstr(s + i, ">>", ft_strlen(s + i)) != NULL)
		{
			ft_printf("Checking2 %s\n", ft_strnstr(s + i, ">>", ft_strlen(s) < 3 ? 3 : ft_strlen(s)));
			if (check_arg(s + i))
				return (0);
		}
		if (s[i] != '\0')
			i++;
	}
	// need to recheck n (number of redir in cmd)
	
	return (1);
}

char        *check_syntax(char *s)
{
	char	*line;
	int 	pos;

	pos = 0;
	line = NULL;
	// This part is only to check Syntax Errors No Appending Yet ? 
	if (ft_strchr(s, '\"') || ft_strchr(s, '\''))
	{
		if (check_quotes(s, &pos) == 0)
		{
			ft_printf("Syntax Error Near %s\n", s + pos);
			return (NULL);
		}
	}
	if (ft_strsearch(s, '|'))
	{
		if (check_pipe(s) == 0)
		{
			ft_printf("Syntax Error Near %s\n", ft_strchr(s, '|'));
			return (NULL);
		}
	}
	if (ft_strchr(s, '>') || ft_strchr(s, '<') || ft_strnstr(s, ">>", (ft_strlen(s) < 3 ? 3: ft_strlen(s))))
	{
		if (check_redir(s) == 0)
		{
			char *e = (ft_strchr(s, '>') == NULL ?  (ft_strchr(s, '<') == NULL ? ft_strnstr(s, ">>", (ft_strlen(s) < 3 ? 3: ft_strlen(s))) : ft_strchr(s, '<')) : ft_strchr(s, '>'));
			ft_printf("Syntax Error Near %s\n", e);
			return (NULL);
		}
	}
	return (s);
}
