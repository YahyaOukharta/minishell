#include "minishell.h"

char    **realloc__(char **s, char *t)
{
    int     i;
    char    **r;
    int     len;

    i = 0;
    len = tab_len(s);
    if (!(r = (char **)malloc(sizeof(char *) * (len + 2))))
        return (NULL);
    while (i < len)
    {
        r[i] = ft_strdup(s[i]);
        if (s[i])
            free(s[i]);
        i++;
    }
    if (s)
        free(s);
    r[i] = ft_strdup(t);
    if (t)
        free(t);
    r[i + 1] = NULL;
    return (r);
}

char            *get_rarg(char *line, int *pos)
{
    int     i;
    int     end;
    int     in;
    char    *s;

    s = NULL;
    i = 0;
    in = 0;
    end = 0;
    while (line[i] != '\0')
    {
        if (QUOTE(line[i]))
	    {
			end = i + 1;
			if (have_end(line + i + 1, line[i], &end))
				in = 1;
		}
		if (i == end)
			in = 0;
		if (ft_isalpha(line[i]) && in == 0)
		{
            while (ft_isalpha(line[i]) && line[i] != '\0' && line[i] != ' ')
            {
                s = append(s, line[i]);
                i++;
            }
			break ;
		}
		s = append(s, line[i]);
		i++;
    }
    if (line[i] == '\0')
        *pos += i - 1;
    else
        *pos += i;
    return (s);
}

t_redir          get_tokens(char *s)
{
    int         i;
    int         end;
    int         in;
    t_redir     redir;
 
    i = 0; 
    end = 0;
    in = 0;
    redir.ins = NULL;
    redir.outs = NULL;
    redir.tokens = NULL;
    while (s[i] != '\0')
    {
        if (QUOTE(s[i]) && in == 0)
        {
			end = i + 1;
			if (inside_quotes(s + i + 1, &end, s[i]))
				in = 1;
        }
        if (i == end + 1)
            in = 0; 
        if (in == 0 && ((s[i] == '>' && s[i + 1] == '>') ||
        s[i] == '>' || s[i] == '<'))
        {
            if (s[i] == '>' && s[i + 1] == '>')
                redir.outs = realloc__(redir.outs, get_rarg(s + i, &i));
            else if (s[i] == '>')
                redir.outs = realloc__(redir.outs, get_rarg(s + i, &i));
            else
                redir.ins = realloc__(redir.ins, get_rarg(s + i, &i));
        }
        else
        {
            if (QUOTE(s[i]))
            {
                i++;
                redir.tokens = realloc__(redir.tokens, inside_quotes(s + i, &i, s[i - 1]));
            }
            else
                redir.tokens = realloc__(redir.tokens, get_arg(s + i, ' ', &i));
        }
        i++;
    }
    return (redir);
}