#include "minishell.h"

int		execute_pipeline(t_pipeline *pipeline)
{
	int		i;
	int		fd[2];
	int		in;
	int		out;
	int		pid;
	i = 0;
	in = 0;
	pid = 0;
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
	while (pid != -1)
		pid = waitpid(-1, &g_status, 0);
	return (g_status);
}
