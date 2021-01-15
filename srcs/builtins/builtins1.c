/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <malaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 15:02:51 by youkhart          #+#    #+#             */
/*   Updated: 2021/01/15 12:52:10 by malaoui          ###   ########.fr       */
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

int		checker(char *s)
{
	int i;

	i = 2;
	if (!(ft_strncmp("-n", s, 2)))
	{
		while (i < (int)ft_strlen(s))
			if (s[i++] != 'n')
				return (0);
		return (1);
	}
	return (0);
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
		while (*argv && ft_strlen(*argv) > 0 && checker(*argv))
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
	t_env	*tmp;

	(void)in;
	(void)out;
	if (tab_len(argv) == 1)
	{
		if (!(tmp = env_with_key("HOME")))
		{
			ft_printf("minishell: cd: HOME not set\n");
			return (1);
		}
		dir = tmp->value;
	}
	else
		dir = argv[1];
	ft_bzero(cwd, 1000);
	getcwd(cwd, 1000);
	dir = ft_strlen(dir) ? dir : ".";
	ret = chdir(dir);
	if (ret < 0)
	{
		ft_printf("minishell: cd: %s: %s\n", dir, strerror(errno));
		return (1);
	}
	if (!(tmp = env_with_key("PWD")))
		set_env("OLDPWD", ft_strdup(""));
	else
		set_env("OLDPWD", ft_strdup(tmp->value));
	ft_bzero(cwd, 1000);
	getcwd(cwd, 1000);
	set_env("PWD", ft_strdup(cwd));
	return (0);
}

int		isallnum(char *s)
{
	int i;
	int len;
	int flag;
	int	sign;

	i = 0;
	len = ft_strlen(s);
	flag = 0;
	sign = 0;
	while (i < len)
	{
		if (s[i] == '-' || s[i] == '+')
		{
			sign++;
			i++;
		}
		if (sign > 1)
			return (0);
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}

char	*skip_blank(char *s)
{
	while (*s && is_blank(*s))
		s++;
	return (s);
}

int		builtin_exit(int in, int out, char **argv)
{
	char	*tmp;

	(void)in;
	(void)out;
	if (tab_len(argv) == 2 && (tmp = skip_blank(argv[1])) && ft_isdigit(tmp[0]))
		g_return = ft_atoi(skip_blank(argv[1]));
	else if (tab_len(argv) == 2 && !isallnum(skip_blank(argv[1])))
		ft_printf("minishell: exit: %s: numeric argument required\n", argv[1]);
	if (tab_len(argv) == 2)
		g_return = (is_number(skip_blank(argv[1])) ? ft_atoi(skip_blank(argv[1])) : 0);
	else if (tab_len(argv) > 2)
		g_return = 1;
	return (-1);
}
