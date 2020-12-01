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
    key = ft_substr(line, 0, i);
    s = env_with_key(key);
    free(key);
    return (s);
}

char        *append_value()
{

    return (NULL);
}

char         *env_to_str(char *line)
{
    int     i;
    int     len;
    char    *s;
    t_env   *env;

    i = 0;
    len = 0;
    s = NULL;
    while (line[i] != '\0')
    {
        if (line[i] == '$')
        {
            i++;
            ft_printf("Looking For%s\n", line + i);
            env = get_env(line + i, &(i));
            if (env != NULL)
                len += ft_strlen(env->value);
            else
                while (ft_isalpha(line[i]) != 0)
                    i++;
        }
        else
        {
            i++;
            len += 1;
        }
    }
    if (!(s = (char *)malloc(sizeof(char ) * (len + 1))))
        return (NULL);
    i = 0;
    int j = 0;
    while (line[i] != '\0' && j < len)
    {
        if (line[i] == '$')
        {
            i++;
            env = get_env(line + i, &(i));
            if (env == NULL)
                while (ft_isalpha(line[i]) != 0)
                    i++;
            else
            {
                ft_strlcpy(s + j, env->value, ft_strlen(env->value) + 1);
                j += ft_strlen(env->value);
            }
        }
        else
        {
            s[j] = line[i];
            j++;
            i++;
        }
    }
    s[j] = '\0';
    return (s);
}

char         *check_line(char *line)
{
    char    *rt;

    rt = NULL;
    // check Syntax
    if (check_syntax(line) == NULL)
        return (NULL);
    // Get env Value
    if (ft_strchr(line, '$'))
        rt = env_to_str(line);
    else
        rt = line;
    
    // append " "
    /*if (ft_strchr(line, '\"') || ft_strchr(line, '\''))
    {

    }*/
    // get $ var 
    return (rt);
}

