#include "minishell.h"

int		execute_pipeline(t_pipeline *pipeline)
{
	int i;
	int fd[2];
	int in;
	int out;

	i = 0;
	in = 0;
	while (i < (pipeline->n_commands) - 1)
	{
		pipe(fd);
		out = fd[1];
		g_status = redirect_outputs(pipeline->cmds[i], in, out);
		close(fd[1]);
		in = fd[0];
		i++;
	}
	out = 1;
	g_status = redirect_outputs(pipeline->cmds[i], in, out);
	return (g_status);
}
