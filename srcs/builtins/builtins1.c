/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <malaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 15:02:51 by youkhart          #+#    #+#             */
/*   Updated: 2021/01/10 17:12:39 by malaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_builtins(void)
{
	int		i;
	char	**tmp;

	i = 0;
	if (!(tmp = ft_split("echo,cd,pwd,export,unset,env,exit", ',')))
		return ;
	while (i < 7)
	{
		g_builtins_str[i] = ft_strdup(tmp[i]);
		free(tmp[i++]);
	}
	free(tmp);
	g_builtins_str[i] = NULL;
	g_builtins[0] = &builtin_echo;
	g_builtins[1] = &builtin_cd;
	g_builtins[2] = &builtin_pwd;
	g_builtins[3] = &builtin_export;
	g_builtins[4] = &builtin_unset;
	g_builtins[5] = &builtin_env;
	g_builtins[6] = &builtin_exit;
}

int		builtin_echo(int in, int out, char **argv)
{
	int endl;

	endl = 1;
	redirect_in_out(in, out);
	if (tab_len(argv) == 1)
		write(1, "\n", 1);
	else
	{
		argv++;
		while (*argv && !ft_strncmp(*argv, "-n", MAX(ft_strlen(*argv), 2)))
		{
			argv++;
			endl = 0;
		}
		while (*argv)
		{
			write(1, *argv, ft_strlen(*argv));
			if (*(argv + 1))
				write(1, " ", 1);
			argv++;
		}
		write(1, "\n", endl);
	}
	return (0);
}

int		builtin_pwd(int in, int out, char **argv)
{
	char buf[1024];

	if (tab_len(argv) != 1)
	{
		printf("pwd: too many arguments\n");
		return (1);
	}
	redirect_in_out(in, out);
	ft_bzero(buf, 1024);
	getcwd(buf, 1024);
	write(1, buf, ft_strlen(buf));
	write(1, "\n", 1);
	return (0);
}

int		builtin_cd(int in, int out, char **argv)
{
	int		ret;
	char	*dir;
	char	cwd[1024];

	in = 0;
	out = 0;
	(void)in;
	(void)out;
	ft_bzero(cwd, 1000);
	getcwd(cwd, 1000);
	if (tab_len(argv) > 2)
	{
		ft_printf("cd: wrong number of arguments\n");
		return (1);
	}
	dir = (tab_len(argv) == 1 ? env_with_key("HOME")->value : argv[1]);
	ret = chdir(dir);
	if (ret < 0)
	{
		ft_printf("cd: no such file or directory: %s\n", dir);
		return (1);
	}
	set_env("OLDPWD", cwd);
	return (0);
}

int		builtin_exit(int in, int out, char **argv)
{
	(void)in;
	(void)out;
	if (tab_len(argv) == 2)
		g_return = (is_number(argv[1]) ? ft_atoi(argv[1]) : 255); 
	else if (tab_len(argv) > 2)
		g_return = 1;
	else
		g_return = g_status;
	return (-1);
}
