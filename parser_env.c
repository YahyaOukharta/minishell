#include "minishell.h"

char        *env_value(char *key)
{
    int     l;
    int     t;
    int     len;
    t_env   s;

    l = 0;
    t = ft_strlen(key);
    len = 0;
    s = *g_env;
    while (s.next != NULL)
    {
        l = ft_strlen(s.key);
        // check the lenght to get correct value (echo $pathlll)
        len = (l > t) ? l : t;
        if (ft_strncmp(s.key, key, len) == 0)
            return ((s.value));
        s = *(s.next);
    }
    return (NULL);
}

char        *get_key(char *s, int *pos)
{
    int     i;
    char    *key;

    i = 0;
    key = NULL;
    if (s[i] == '$')
        i++;
    while (s[i] != '\0')
    {
        if (ft_isalnum(s[i]) == 0)
        {
            i--;
            break ;
        }
        i++;
    }
    key = ft_substr(s, 1, i);
    *pos += i;
    return (key);
}

int         ft_count_char(char *s, char c)
{
    int     i;
    int     n;

    i = 0;
    n = 0;
    while (s[i] != '\0')
        if (s[i++] == c)
            n++;
    return (n);
}

t_env         *get_env(char *line, int *pos)
{
    int     i;
    char    *key;
    t_env   *s;
    i = 0;
    key = NULL;
    while (line[i] != '\0')
    {
        if (ft_isalpha(line[i]) == 0)
            break ;
        *pos += 1;
        i += 1;
    }
    if (line[i] == '\0')
        *pos -= 1;
    key = ft_substr(line, 0, i);
    s = env_with_key(key);
    free(key);
    return (s);
}

char         *env_to_str(char *line)
{
    int     i;
    char    *s;
    t_env   *env;
    int     in;
    int     end;
    char    *tmp;
    char    quote;

    i = 0;
    s = NULL;
    in = 0;
    end = 0;
    tmp = NULL;
    while (line[i] != '\0')
    {
        if (QUOTE(line[i]) && in == 0)
        {
            quote = line[i];
            end = i + 1;
            if (inside_quotes(line + i + 1, &end, line[i]))
                in = 1;
        }
        if (i == end + 1)
            in = 0;
        if ((in == 0 || quote != '\'') && line[i] == '$')
        {
            i++;
            env = get_env(line + i, &(i));
            i++;
            if (env != NULL)
            {
                //inside single or Double Quotes ?? hmm
                tmp = ft_strdup(s);
                if (s)
                    free(s);
                s = ft_strjoin(tmp, ft_strdup(env->value));
                if (tmp)
                    free(tmp);
                // if (line[i + 1] == '\0' && !ft_isalpha(line[i]))
                //     i--;
            }
        }
        tmp = ft_strdup(s);
        s = append(tmp, line[i]);
        i++;
    }
    return (s);
}
