#include "minishell.h"

void		ft_minishell(char **env)
{
	char	*line;
	int		rt;
	t_pipeline	**parsed_line;

	rt = 0;
	init_shell(env);
	while (g_status != -1)
	{
		line = NULL;
		rt = ft_prompt(&line);
		if (handle_return(rt, line) == true)
			continue ;
		if (!(parsed_line = parse_data(line)))
			continue ;
		exec_parsed(parsed_line);
		free(line);
	}
}

int			main(int ac, char **argv, char **env)
{
	if (ac == 1)
		ft_minishell(env);
	else
		ft_printf("Usage : ./minishell\n");
	return (0);
}
