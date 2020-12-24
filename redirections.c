#include "minishell.h"

char	*jump_redirection_sign(char *out)
{
	char	*s;
	int		i;
	char	quote;

	i = 0;
	s = NULL;
	while (*out == '>' || *out == '<' || is_blank(*out))
		out++;
	if (QUOTE(*out))
	{
		quote = *out;
		out++;
		s = inside_quotes(out, &i, quote);
	}
	else
		s = ft_strdup(out);
	return (s);
}

int		redirect_inputs(char **tokens, int out, int pipe_in, char **input_files)
{
	int		i;
	char	*tmp;
	int		fd;
	char	*parsed;

	parsed = NULL;
	if (!(pipe_in == 0 && tab_len(input_files)))
		g_status = execute_command(pipe_in, out, tokens);
	i = 0;
	while (i < tab_len(input_files))
	{
		parsed = jump_redirection_sign(input_files[i]);
		fd = open(parsed, O_RDONLY);
		free(parsed);
		if (fd < 0)
		{
			tmp = "minishell: no such file or directory: %s\n";
			ft_printf(tmp, input_files[i]);
			return (1);
		}
		g_status = execute_command(fd, out, tokens);
		close(fd);
		i++;
	}
	return (g_status);
}

int		truncate_file(char *out)
{
	int i;

	i = 0;
	while (out[i] == '>')
		i++;
	return (i == 2 ? O_APPEND : O_TRUNC);
}

int		redirect_outputs(t_command *cmd, int pipe_in, int pipe_out)
{
	int		i;
	int		fd;
	char	*tmp;
	char	*parsed;

	parsed = NULL;
	while (i < tab_len(cmd->output_files))
	{
		parsed = jump_redirection_sign(cmd->output_files[i]);
		fd = open(parsed,
			truncate_file(tmp) | O_CREAT | O_WRONLY, 0644);
		free(parsed);
		if (fd < 0)
		{
			ft_printf("No such file or Directory\n");
			i++;
			continue;
		}
		if (i == tab_len(cmd->output_files) - 1)
			g_status = redirect_inputs(cmd->tokens, fd,
				pipe_in, cmd->input_files);
		close(fd);
		i++;
	}
	if (!(pipe_out == 1  && tab_len(cmd->output_files))
		|| (cmd->tokens != NULL && string_equal(cmd->tokens[0], "exit")))
		g_status = redirect_inputs(cmd->tokens,
			pipe_out, pipe_in, cmd->input_files);
	return (g_status);
}
