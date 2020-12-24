#include "minishell.h"

char        *inside_quotes(char *s, int *start, char quote)
{
    int     i;
    int     end;
    char    *m;
    char    *tmp;
    char    *rt;

    i = 0;
    end = 0;
    m = NULL;
    tmp = NULL;
    rt = NULL;
    while (s[i] != '\0')
    {
        if (s[i] == quote && !(ft_isalnum(s[i + 1])))
        {
            *start += i;
            break ;
        }
        else if (s[i] == quote && ft_isalnum(s[i + 1]))
        {
            i++;
            // echo " f f f f  f " > sdf" v fedfsdf d d f"fdf
            tmp = outside_quotes(s + i, &i);
            rt = ft_strdup(m);
            if (m)
                free(m);
            m = ft_strjoin(rt, tmp);
            free(tmp);
            free(rt);
            *start += i;
            break ;
        }
        m = append(m, s[i]);
        i++; 
    }
    return (m);
}

char        *outside_quotes(char *s, int *start)
{
    int     i;
    char    *m;
    char    *rt;
    char    *tmp;
    char    *t;

    tmp = NULL;
    i = 0;
    m = NULL;
    rt = NULL;
    t = NULL;
    while (s[i] != '\0')
    {
        if (s[i] == ' ' || s[i] == '>' || s[i] == '<')
        {
            *start += i;
            break ;
        }
        if (QUOTE(s[i]))
        {
            i++;
            tmp = ft_strdup(rt);
            if (rt != NULL)
                free(rt);
            t = inside_quotes(s + i, &i, s[i - 1]);
            rt = ft_strjoin(tmp, t);
            if (t)
                free(t);
            if (tmp)
                free(tmp);
        }
        else
            rt = append(rt, s[i]);
        if (s[i] != ' ')
            i++;
    }
    if (s[i] == '\0')
        *start += i - 1;
    return (rt);
}

char        *ft_get_value(char *line, int *pos)
{
    int     i;
    char    *s;
    char    *key;
    t_env   *env;


    i = 0;
    s = NULL;
    key = NULL;
    while (line[i] != '\0' && ft_isalnum(line[i]))
        i++;
    key = ft_substr(line, 0, i);
    env = env_with_key(key);
    if (env != NULL)
        s = ft_strdup(env->value);
    else
        s = ft_strdup("");
    if (key)
        free(key);
    *pos += i;
    return (s);
}

char        *handle_env(char *line, int *pos)
{
    char    *s;
    int     i;
    char    *tmp;
    char    *p;

    s = NULL;
    tmp = NULL;
    i = 0;
    p = NULL;
    while (line[i] == '$' && line[i + 1] == '$')
    {
        tmp  = ft_strdup(s);
        if (s)
            free(s);
        s = ft_strjoin(tmp, ft_itoa(g_child));
        if (tmp)
            free(tmp);
        i += 2;
    }
    if (line[i] == '$' && line[i + 1] == '?')
    {
        tmp  = ft_strdup(s);
        if (s)
            free(s);
        s = ft_strjoin(tmp, ft_itoa(g_status));
        if (tmp)
            free(tmp);
        i += 2;
    }
    else if (line[i] == '$')
    {
        i++;
        tmp  = ft_strdup(s);
        if (s)
            free(s);
        p = ft_get_value(line + i, &i);
        s = ft_strjoin(tmp, ((ft_strlen(p) == 0) ? "$" : p));
        if (tmp)
            free(tmp);
    }
    *pos += i;
    return (s);
}

t_exp       inp(char *s)
{
    int     i;
    t_exp   in;
    int     end;
    t_exp   num;

    i = 0;
    end = 0;
    in.sgl = 0;
    in.dbl = 0;
    while (s[i] != '\0')
    {
        if (QUOTE(s[i]))
        {
            if (have_end(s + i + 1, s[i], &end) && s[i] == '\'')
                in.sgl += 1;
            if (have_end(s + i + 1, s[i], &end) && s[i] == '\"')
                in.dbl += 1;
        }
        if (s[i] == '$')
            return (in);
        i++;
    }
    return (in);
}

char         *ft_env(char *line)
{
    int     i;
    char    *s;
    char    *tmp;
    t_exp   in;

    i = 0;
    s = NULL;
    tmp = NULL;
    in.sgl = 0;
    in.dbl = 0;
    while (line[i] != '\0')
    {
        if (QUOTE(line[i]))
        {
            in = inp(line + i);
            while (QUOTE(line[i]))
            {
                s = append(s, line[i]);
                i++;
            }
        }
        if (line[i] == '$' && (in.sgl > 1 || in.dbl > 0 || (in.sgl == in.dbl)))
        {
            tmp = ft_strdup(s);
            if (s)
                free(s);
            s = ft_strjoin(tmp, handle_env(line + i, &i));
            if (tmp)
                free(tmp);
        }   
        else if (line[i] != '\0')
        {
            s = append(s, line[i]);
            i++;
        }
    }
    return (s);
}

char         *check_line(char *line)
{
    char    *tmp;
    char    *rt;

    rt = ft_strdup(line);
    tmp = NULL;
    if (!(tmp = check_syntax(line)))
    {
        free(rt);
        free(tmp);
        return (NULL);
    }
    if (ft_strchr(line, '$'))
    {
        tmp = ft_strdup(rt);
        if (rt)
            free(rt);
        rt = ft_env(tmp);
    }
    if (tmp)
        free(tmp);
    return (rt);
}
