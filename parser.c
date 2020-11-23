#include "minishell.h"

char 	*get_command(char *line)
{
	int i;
	int quotes;

	quotes = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '\"')
			quotes = (quotes + 1) % 2;
		if ((line[i] == '<' || line[i] == '>') && !quotes)
			break;
		i++;
	}
	return (ft_substr(line, 0, i));
}

int get_n_input_files(char *line, int index)
{
	int count;
	int quotes;

	quotes = 0;
	count = 0;
	while (line[index])
	{
		if (line[index] == '\"')
			quotes = (quotes + 1) % 2;
		if (line[index] == '<' && !quotes)
			count++;
		index++;
	}
	return (count);
}

int get_n_output_files(char *line, int index)
{
	int count;
	int quotes;

	quotes = 0;
	count = 0;
	while (line[index])
	{
		if (line[index] == '\"')
			quotes = (quotes + 1) % 2;
		if (line[index] == '>'&& (!index || line[index - 1] != '>') && !quotes)
			count++;
		index++;
	}
	return (count);
}

int get_file_name_len(char *str)
{
	int i;

	i = 0;
	while (str[i] && !is_blank(str[i]) && !ft_strchr("<>", str[i]))
		i++;
	return (i);
}

char **get_input_files(char *line, int index)
{
	int i;
	int count;
	int quotes;
	char **tab;
	int j;

	quotes = 0;
	tab = (char **)malloc(sizeof(char *) * (get_n_input_files(line, index) + 1));
	i = index;
	j = 0;
	while (line[i])
	{
		if (line[i] == '\"')
			quotes = (quotes + 1) % 2;
		if (line[i] == '<' && !quotes)
		{
			i++;
			while (is_blank(line[i]))
				i++;
			tab[j] = ft_substr(line, i, get_file_name_len(&line[i]));
			j++;
			i += get_file_name_len(&line[i]) - 1;
		}
		i++;
	}
	tab[j] = 0;
	return (tab);
}

char **get_output_files(char *line, int index)
{
	int i;
	int count;
	int quotes;
	char **tab;
	int j;
	int k;

	quotes = 0;
	tab = (char **)malloc(sizeof(char *) * (get_n_output_files(line, index) + 1));
	i = index;
	j = 0;

	while (line[i])
	{
		if (line[i] == '\"')
			quotes = (quotes + 1) % 2;
		if (line[i] == '>' && !quotes)
		{
			i++;
			if(line[i] == '>')
			{
				k = 2;
				i++;
			}
			else
				k = 1;
			while (is_blank(line[i]))
			{
				i++;
				k++;
			}
			tab[j] = ft_substr(line, i - k, get_file_name_len(&line[i]) + k);
			j++;
			i += get_file_name_len(&line[i]) - 1;
		}
		i++;
	}
	tab[j] = 0;
	return (tab);
}

t_command *new_cmd(char *line)
{
    t_command *cmd = (t_command *)malloc(sizeof(t_command));

    char *s = get_command(line);
	printf("cmd without io <%s>\n",s);
    cmd->tokens = ft_split(s, ' ');
    cmd->input_files = get_input_files(line,ft_strlen(s));

    cmd->output_files = get_output_files(line,ft_strlen(s));

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
	return (pipeline);
}

t_pipeline **mini_parser(char *line)
{
    char **pipelines;
    char **cmds;

	line = ft_strtrim(line," \t");
    pipelines = ft_split(line,';');

	t_pipeline **parsed_line = (t_pipeline **)malloc(sizeof(t_pipeline*) * (tab_len(pipelines)+1));

	int i = 0;
	while(pipelines[i])
	{
		parsed_line[i] = new_pipeline(ft_split(pipelines[i], '|'));
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
	while (parsed_line[i])
	{
		j = 0;
		ft_printf("Pipeline %d : \n" ,i+1 );
		while (parsed_line[i]->cmds[j])
		{
			ft_printf("\tCommand %d :\n", j+1);

			k=0;
			ft_printf("\t  Tokens : ");
			while (parsed_line[i]->cmds[j]->tokens[k])
			{	
				ft_printf("%s ",parsed_line[i]->cmds[j]->tokens[k]);
				k++;
			}
			ft_printf("\n");
			k=0;
			ft_printf("\t  Inputs : ");
			while (parsed_line[i]->cmds[j]->input_files[k])
			{	
				ft_printf("%s ",parsed_line[i]->cmds[j]->input_files[k]);
				k++;
			}
			ft_printf("\n");
			k=0;
			ft_printf("\t  Outputs : ");
			while (parsed_line[i]->cmds[j]->output_files[k])
			{	
				ft_printf("%s ",parsed_line[i]->cmds[j]->output_files[k]);
				k++;
			}
			ft_printf("\n");
			j++;
		}
		i++;
	}
}