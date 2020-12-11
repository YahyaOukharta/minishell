#include "minishell.h"


int			quotes_attached(char *s)
{
	int i;

	i = 0;
	while (ft_isalpha(s[i]) && s[i] != '\0')
		i++;
	if (QUOTE(s[i]))
		return (1);
	return (0);
}

char		**fml_parser(char *line)
{
	int     i;
    char    quote;
    int     k;
	char	**s;


    k = 0;
    i = 0;
    quote = 0;
	s = NULL;
    while (line[i] != '\0')
    {
        if (QUOTE(line[i]))
        {
            i++;
            inside_quotes(line + i, &i, line[i - 1]);
            k++;
        }
        else
        {
            outside_quotes(line + i, &i);
            k++;
            i++;
        }
    }
	if (!(s = (char **)malloc(sizeof(char *) * (k + 1))))
		return (NULL);
	i = 0;
	k = 0;
	while (line[i] != '\0')
    {
        if (QUOTE(line[i]))
        {
            i++;
            s[k] = inside_quotes(line + i, &i, line[i - 1]);
            k++;
        }
        else
        {
			if (quotes_attached(line + i))
				s[k] = outside_quotes(line + i, &i);
			else
				s[k] = ft_strtrim(outside_quotes(line + i, &i), " ");
            k++;
            i++;
        }
    }
	s[k] = NULL;
	return (s);
}

int		cparser(char *s, char q)
{
	int i;
	int in;
	int c;

	i = 0;
	in = 0;
	c = 0;
	while (s[i] != '\0')
	{
		if (QUOTE(s[i]))
		{
			if (have_end(s + i + 1, s[i], &i))
				in = 1;
			else
				in = 0;
		}
		if (in == 0 && s[i] == q)
			c++;
		i++;
	}
	return (c);
}

char	*append(char *s, char c)
{
	char	*str;
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(s);
	if (!(str = malloc(sizeof(char ) * (len + 2))))
		return (NULL);
	while (i < len)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = c;
	str[i + 1] = '\0';
	return (str);
}

char	*get_arg(char *line, char c, int *pos)
{
	int 	i;
	int 	end;
	int 	in;
	char	*s;
	char 	*tmp;

	i = 0;
	end = 0;
	in = 0;
	s = NULL;
	tmp = NULL;
	while (line[i] != '\0')
	{
		if (QUOTE(line[i]))
		{
			end = i + 1;
			if (have_end(line + i + 1, line[i], &end))
				in = 1;
		}
		if (i == end + 1)
			in = 0;
		if (line[i] == c && in == 0)
		{
			*pos += i;
			break ;
		}
		s = append(s, line[i]);
		i++;
	}
	return (s);
}

char	**parser_split(char *line, char c)
{
	int	 	i;
	int		nb_c;
	char 	**split;
	int		j;

	i = 0;
	j = 0;
	nb_c = cparser(line, c) + 1;
	if (!(split = (char **)malloc(sizeof(char *) * (nb_c + 1))))
		return (NULL);
	i = 0;
	while (i < nb_c)
	{
		split[i] = get_arg(line + j, c, &j);
		j++;
		i++;
	}
	split[i] = NULL;
	return (split);
}
 