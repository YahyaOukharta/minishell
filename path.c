#include "minishell.h"

extern t_env	*g_env;

char			**get_parsed_path(void)
{
	t_env *env;

	if (!g_env)
		return (0);
	env = env_with_key("PATH");
	if (env)
		return (ft_split(env->value, ':'));
	return (0);
}

int				find_file_in_path(char **str, char *cmd)
{
	char		**path;
	int			i;
	struct stat	buf;

	i = 0;
	*str = NULL;
	if (ft_strchr(cmd, '/') && !stat(cmd, &buf))
	{
		*str = ft_strdup(cmd);
		return (1);
	}
	path = get_parsed_path();
	while (path[i])
	{
		*str = ft_strjoin_va(3, path[i], "/", cmd);
		if (!stat(*str, &buf))
		{
			free_s_tab(path);
			return (1);
		}
		free(*str);
		i++;
	}
	*str = NULL;
	return (free_s_tab(path));
}
