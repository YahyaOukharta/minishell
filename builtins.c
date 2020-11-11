#include "minishell.h"

void    init_builtins()
{
    int     i;
    char    **tmp;

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
	//g_builtins[1] = &builtin_cd;
	g_builtins[2] = &builtin_pwd;
	g_builtins[3] = &builtin_export;
	g_builtins[4] = &builtin_unset;
	g_builtins[5] = &builtin_env;
	g_builtins[6] = &builtin_exit;
}

int     builtin_echo(int in, int out, char **argv)
{
	int endl;
	int i;
	
	endl = 1;
	//redirect_in_out(in, out);
	if (tab_len(argv) == 1)
		write(1, "\n", 1);
	else
	{
		argv++;
		if (!ft_strncmp(*argv, "-n",max(ft_strlen(*argv), 2)))
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
		if (endl)
			write(1, "\n", 1);
	} 
	return (0);
}

int     builtin_pwd(int in, int out, char **argv)
{
	char buf[1024];

	if (tab_len(argv) != 1)
	{
		printf("pwd: too many arguments\n");
		return(1);
	}
	//redirect_in_out(in, out);
	ft_bzero(buf, 1024);
	getcwd(buf, 1024);
	write(1, buf, ft_strlen(buf));
	write(1, "\n", 1);
	return (0);
}

int     builtin_cd(int in, int out, char **argv)
{
	int ret;
	char *dir;

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
	return (0);
}

int     builtin_env(int in, int out, char **argv)
{
	t_env   *env;

	if (tab_len(argv) != 1)
	{
		printf("env: too many arguments\n");
		return (1);
	}
	//redirect_in_out(in, out);
	env = g_env;
	while (env)
	{
		printf("%s=%s\n",env->key, env->value);
		env = env->next;
	}
	return (0);
}

int     builtin_export(int in, int out, char **argv)
{
	char    **tab;
	int     i;

	(void)in;
	(void)out;
	if (tab_len(argv) > 1)
	{
		i = 1;
		while (argv[i])
		{
			tab = ft_split(argv[i], '=');
			if (tab_len(tab) == 2)
				set_env(tab[0], tab[1]);
			if (tab_len(tab) == 1 && argv[i][ft_strlen(argv[i]) - 1] == '=')
				set_env(tab[0], ft_strdup(""));
			//free_s_tab(tab);
			i++;
		}
	}
	return (0);
}

int     builtin_unset(int in, int out, char **argv)
{
	char    **tab;
	int     i;

	if (tab_len(argv) > 1)
	{
		//redirect_in_out(in, out);
		i = 1;
		while (argv[i])
		{
			tab = ft_split(argv[i], '=');
			if (tab_len(tab) == 1)
				unset_env(tab[0]);
			free_s_tab(tab);
			i++;
		}
	}
	return (0);
}

int     builtin_exit(int in, int out, char **argv)
{
	(void)argv;
	exit(-1);
}