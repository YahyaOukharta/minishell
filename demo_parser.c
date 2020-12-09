#include "minishell.h"

int		fml_parser(char *line, t_parser *parsed)
{
	int     i;
    char    quote;
    int     k;

    k = 0;
    i = 0;
    quote = 0;
    while (line[i] != '\0')
    {
        parsed->inside = 0;
        parsed->outside = 0;
        if (QUOTE(line[i]))
        {
            i++;
            parsed[k].args = inside_quotes(line + i, &i, line[i - 1]);
            parsed->inside = 1;
            k++;
        }
        else
        {
            parsed[k].args =  outside_quotes(line + i, &i);
            parsed->outside = 1;
            k++;
            i++;
        }
    }
	return (k);
}

t_command *get_n_pipes(char *line)
{
return NULL;
}

t_pipeline	*get_n_commands(t_parser *parsed, int start, int end)
{
	t_pipeline *pipeline = (t_pipeline *)malloc(sizeof(t_pipeline));
	int i = start;
	int n_pipes = 0;
	while (i < end)
	{
		if (ft_strchr(parsed[i].args, '|') && parsed[i].outside == 1)
			n_pipes += 1;
		i++;
	}
	pipeline->cmds = (t_command **)malloc(sizeof(t_command *) * (n_pipes + 1));
	i = 0;
	while (i < n_pipes)
	{
		//pipeline->cmds[i] = get_n_pipes();
		i++;
	}
}

int		has_char(char *s, char c)
{
	int i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

t_pipeline  **parser(char *line)
{
    t_parser    parsed[50];
    int c = fml_parser(line, parsed);
    int i = 0;
	int n_cmds = 0;
	int n_pipes = 0;
	int	n_redir = 0;
    while (i < c)
    {
        parsed[i].inside == 1 ? ft_printf("inside |%s|\n", parsed[i].args) : ft_printf("outside |%s|\n", parsed[i].args);
		ft_printf("Looking in : %s| GOT %d\n", ft_strchr(parsed[i].args, ';'), has_char(parsed[i].args, ';'));
	    if (has_char(parsed[i].args, ';') == 1 && parsed[i].outside == 1)
			n_cmds += 1;
		// if (ft_strchr(parsed[i].args, '|') && parsed[i].outside == 1)
		// 	n_pipes += 1;clear
		
		/*
			Redirs To check after unit test
			if (ft_strchr(parsed[i].args, ';') && parsed[i].outside == 1)
				n_cmds += 1;
		*/
		i++;
    }
	ft_printf("Number of commands : %d | Number Of Pipes : %d\n", n_cmds, n_pipes);
    t_pipeline **cmd;

	cmd = (t_pipeline **)malloc(sizeof(t_pipeline *) * (n_cmds + 1));
	i = 0;
	int start = 0;

	// while (i < c)
	// {
	// 	if (ft_strchr(parsed[i].args, ';') && parsed[i].outside == 1)
	// 	{
	// 		cmd[i] = get_n_commands(parsed, start, i);
	// 		start = i;
	// 	}
	// 	i++;
	// }
	// Looking For ; && | then  Parse accordingly
	// ; Create A new Pipeline
	/*
		get_n_pipelines();
	*/
	// | Create A new Command 
	/*
		get_n_command();
	*/
    return (cmd);
}