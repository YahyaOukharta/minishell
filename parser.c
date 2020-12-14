#include "minishell.h"

char	**remove_extras(char **s)
{
	int i;
	char **str;
	int len;
	int	j;

	i = 0;
	len = tab_len(s);
	j = 0;
	if (!(str = (char **)malloc(sizeof(char *) * (tab_len(s) + 1))))
		return (NULL);
	while (i < len)
	{
		if (ft_strlen(s[i]) == 0)
			i++;
		str[j] = ft_strtrim(s[i], "\'\"");
		if (s[i])
			free(s[i]);
		i++;
		j++;
	}
	if (s)
		free(s);
	str[j] = NULL;
	return	(str);
}

t_command *new_cmd(char *line)
{
    t_command *cmd = (t_command *)malloc(sizeof(t_command));
	t_redir		redir;

	ft_printf("|%s|\n", line);
    // char *s = get_command(line);
	redir = get_tokens(line);
    cmd->tokens = remove_extras(redir.tokens);
	//cmd->tokens = redir.tokens;
    cmd->input_files = redir.ins;
    cmd->output_files = redir.outs;
    return (cmd);
}

t_pipeline *new_pipeline(char **lines)
{
	t_pipeline *pipeline = (t_pipeline *)malloc(sizeof(t_pipeline));

	pipeline->cmds = (t_command **)malloc(sizeof(t_command *) * (tab_len(lines) + 1));
	int i = 0;
	while (lines[i])
	{
		pipeline->cmds[i] = new_cmd(lines[i]);
		i++;
	}
	pipeline->cmds[i] = 0;
	pipeline->n_commands = i;
	return (pipeline);
}

t_pipeline **parser(char *line)
{
    char **pipelines;
    char **cmds;

	line = ft_strtrim(line," \t");
    pipelines = parser_split(line,';');

	t_pipeline **parsed_line = (t_pipeline **)malloc(sizeof(t_pipeline*) * (tab_len(pipelines) + 1));

	int i = 0;
	while(pipelines[i] != NULL)
	{
		parsed_line[i] = new_pipeline(parser_split(pipelines[i], '|'));
		i++;
	}	
	parsed_line[i] = 0;
	return (parsed_line);
}

void print_parsed_line(t_pipeline **parsed_line)
{
	int i;
	int j;
	int k;

	i = 0;
	if (parsed_line)
	{
		while (parsed_line[i])
		{
			j = 0;
			ft_printf("***Pipeline %d ***\n" ,i+1 );
			if (parsed_line[i]->cmds)
			{
				while (parsed_line[i]->cmds[j])
				{
					ft_printf("\t**** Command %d ****\n", j+1);

					k=0;
					ft_printf("\t  Tokens : ");
					if (parsed_line[i]->cmds[j]->tokens)
					{
						while (parsed_line[i]->cmds[j]->tokens[k])
						{	
							ft_printf("|%s| ",parsed_line[i]->cmds[j]->tokens[k]);
							k++;
						}
					}
					ft_printf("\n");
					k=0;
					ft_printf("\t  Inputs : ");
					if (parsed_line[i]->cmds[j]->input_files)
					{
						while (parsed_line[i]->cmds[j]->input_files[k])
						{	
							if ((parsed_line[i]->cmds[j]->input_files[k]) != NULL)
								ft_printf("%s ",parsed_line[i]->cmds[j]->input_files[k]);
							k++;
						}
					}
					ft_printf("\n");
					k=0;
					ft_printf("\t  Outputs : ");
					if (parsed_line[i]->cmds[j]->output_files)
					{
						while (parsed_line[i]->cmds[j]->output_files[k])
						{	
							ft_printf("%s ",parsed_line[i]->cmds[j]->output_files[k]);
							k++;
						}
					}
					ft_printf("\n");
					j++;
				}
			}
			i++;
		}
	}
	//ft_printf("\n");
}