#include "minishell.h"


int			have_end(char *s, char quote, int start)
{
	while (start < ft_strlen(s))
	{
		if (s[start] == quote)
			return (1);
		start++;
	}
	return (0);
}

int			check_quotes(char	*s)
{
	int 	i;
	int 	start;
	int		end;
	char	quote;

	i = 0;
	start = 0;
	end = ft_strlen(s);
	quote = '0';
	while (start < end / 2)
	{
		if (s[start] == '\'' || s[start] == '\"')
		{
			quote = s[start++];
			if (have_end(s, quote, start) == 0)
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

	i = 0;
	if (s)
	{
		while (s[i] != '\0')
		{
			if (ft_isalpha(s[i]) || ft_isdigit(s[i]))
				return (0);
			if (s[i] == '>' || s[i] == '<' || ft_strncmp(s, ">>", ft_strlen(s) < 3 ? 3 : ft_strlen(s)) == 0)
				return (1);
			i++;
		}
	}
	return (1);
}

int			check_redir(char *s)
{
	if (ft_strchr(s, '>') && !ft_strnstr(s, ">>", ft_strlen(s)))
	{
		//ft_printf("Checking %s\n", ft_strchr(s, '>') + 1);
		if (check_arg(ft_strchr(s, '>') + 1))
			return (0);
	}
	if (ft_strchr(s, '<') && !ft_strnstr(s, "<<", ft_strlen(s)))
	{
		//ft_printf("Checking %s\n", check_arg(ft_strchr(s, '<')));
		if (check_arg(ft_strchr(s, '<') + 1))
			return (0);
	}
	if (ft_strnstr(s, ">>", ft_strlen(s)) != NULL)
	{
		//ft_printf("Checking %s\n", ft_strnstr(s, ">>", ft_strlen(s) < 3 ? 3 : ft_strlen(s)));
		if (check_arg(ft_strnstr(s, ">>", ft_strlen(s) < 3 ? 3 : ft_strlen(s))))
			return (0);
	}
	// need to recheck n (number of redir in cmd)
	return (1);
}

char        *check_syntax(char *s)
{
	char	*line;

	line = NULL;
	// This part is only to check Syntax Errors No Appending Yet ? 
	if (ft_strchr(s, '\"') || ft_strchr(s, '\''))
	{
		if (check_quotes(s) == 0)
		{
			ft_printf("Syntax Error Near %s\n", ft_strchr(s, '\'') == NULL ? ft_strchr(s, '\"') : ft_strchr(s, '\''));
			return (NULL);
		}
	}
	if (ft_strchr(s, '|'))
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
	/*// check $
	if (ft_strchr(s, '$'))
	{

	}
	// check redir
	*/
	return (s);
}
