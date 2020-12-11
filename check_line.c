#include "minishell.h"


char        *inside_quotes(char *s, int *start, char quote)
{
    int     i;
    int     end;
    char    *m;

    i = 0;
    end = 0;
    m = NULL;
    while (s[i] != '\0')
    {
        if (s[i] == quote)
        {
            end = i++;
            *start += i;
            break ;
        }
        i++;
    }
    if (!(m = ft_substr(s, 0, end)))
        return (NULL);
    return (m);
}

char        *outside_quotes(char *s, int *start)
{
    int     i;
    char    *m;
    char    *rt;
    char    *tmp;
    char    p[2];
    tmp = NULL;
    i = 0;
    m = NULL;
    rt = NULL;
    while (s[i] != '\0')
    {
        if (s[i] == ' ' && i != 0)
        {
            *start += i;
            break ;
        }
        if (QUOTE(s[i]))
        {
            tmp = ft_strdup(rt);
            if (rt != NULL)
                free(rt);
            rt = ft_strjoin(tmp, inside_quotes(s + i, &i, s[i]));
            if (tmp)
                free(tmp);
        }
        else 
        {
            p[0] = s[i];
            p[1] = '\0';
            if (rt == NULL)
                rt = ft_strdup("");
            tmp = ft_strjoin(rt, p);
            if (rt != NULL)
                free(rt);
            rt = ft_strdup(tmp);
            if (tmp)
                free(tmp);
            i++;
        }
    }
    if (s[i] == '\0')
        *start += i - 1;
    return (rt);
}

char        *quotes_to_hell(char *line)
{
    int     i;
    char    quote;
    char    *append;
    char    *tmp;
    char    *data;

    i = 0;
    quote = 0;
    append = NULL;
    tmp = NULL;
    while (line[i] != '\0')
    {
        data = NULL;
        tmp = NULL;
        if (QUOTE(line[i]))
        {
            i++;
            //ft_printf("inside : %s\n", inside_quotes(line + i, &i, line[i - 1]));
            tmp = ft_strdup(append);
            if (append)
                free(append);
            data = inside_quotes(line + i, &i, line[i - 1]);
            append = ft_strjoin(tmp, data);
            if (tmp)
                free(tmp);
            if (data)
                free(data);
        }
        else
        {
            //ft_printf("outside : %s\n", outside_quotes(line + i, &i));
            tmp = ft_strdup(append);
            if (append)
                free(append);
            data = outside_quotes(line + i, &i);
            append = ft_strjoin(tmp, data);
            if (tmp)
                free(tmp);
            if (data)
                free(data);
            i++;
        }
        // if (line[i] == ' ')
        //     i++;
    }
    return (append);
}

char         *check_line(char *line)
{
    char    *rt;
    char    *tmp;

    tmp = NULL;
    rt = ft_strdup(line);
    // check Syntax
    if (check_syntax(line) == NULL)
        return (NULL);
    // Get env Value
    if (ft_strchr(line, '$'))
    {
        tmp = ft_strdup(rt);
        if (rt)
            free(rt);
        rt = env_to_str(tmp);
        if (tmp)
            free(tmp);
    }
    // append " "
    /*if (ft_strchr(line, '\"') || ft_strchr(line, '\''))
    {
        tmp = ft_strdup(rt);
        if (rt)
            free(rt);
        rt = quotes_to_hell(tmp);
        if (tmp)
            free(tmp);
    }*/
    // get $ var 
    ft_printf("line to exec %s\n", rt);
    return (rt);
}


