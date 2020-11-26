#include "minishell.h"

int redirect_inputs(char **tokens, int out, int pipe_in, char **input_files)
{
    int i;
    char *tmp;
	int fd;

	if (!(pipe_in == 0 && tab_len(input_files)))
		g_status = execute_command(pipe_in, out, tokens);

	i = 0;
	while (i < tab_len(input_files))
	{
		fd = open(input_files[i], O_RDONLY);
		if (fd < 0)
        {
            ft_printf("minishell: no such file or directory: %s\n", input_files[i]);
            return (1);
        }
		g_status = execute_command(fd, out, tokens);
		close(fd);
		i++;
	}
    return (g_status);
}

char *jump_redirection_sign(char *out)
{
    while (*out == '>' || is_blank(*out))
        out++;
    return (out);
}

int truncate_file(char *out)
{
    int i = 0;
    while (out[i] == '>')
        i++;
    return (i == 2 ? 0 : O_TRUNC); 
}

int  redirect_outputs(t_command *cmd, int pipe_in, int pipe_out)
{
	int i;
	int fd;
    char *tmp;

	i = 0;
	while (i < tab_len(cmd->output_files))
	{
        tmp = cmd->output_files[i];
		fd = open(jump_redirection_sign(tmp), truncate_file(tmp) | O_CREAT | O_WRONLY | O_APPEND, 0644); // O_TRUNC only if >
		g_status = redirect_inputs(cmd->tokens, fd, pipe_in, cmd->input_files);
		close(fd);
		i++;
	}
	if (!(pipe_out == 1  && tab_len(cmd->output_files))) // ls | grep 'filename' > out , doesnt print anything
		g_status = redirect_inputs(cmd->tokens, pipe_out, pipe_in, cmd->input_files);
	return (g_status);
}
