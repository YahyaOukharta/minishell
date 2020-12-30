/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <malaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 18:45:36 by youkhart          #+#    #+#             */
/*   Updated: 2020/12/30 11:59:40 by malaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "ft_printf.h"
# include "get_next_line.h"
# include <stdbool.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <signal.h>
# include <stdio.h>

# define STDOUT 1
# define STDIN  0
# define STDERR 2
# define QUOTE(x)   (x == '\'' || x == '\"') ? 1 : 0
# define MAX(a , b) (a > b ? a : b)

int					g_status;
int					g_signal_c;
int					g_signal_d;
pid_t				g_child;
int					g_return;
char				*g_line;
char				*g_saved;
int					g_exec;
int					g_signal_bs;

typedef struct		s_exp
{
	int				sgl;
	int				dbl;
}					t_exp;

typedef struct		s_command
{
	char			**tokens;
	char			**input_files;
	char			**output_files;
}					t_command;

typedef struct		s_pipeline
{
	t_command		**cmds;
	int				n_commands;
}					t_pipeline;

typedef struct		s_redir
{
	char			**ins;
	char			**outs;
	char			**tokens;
}					t_redir;

typedef struct		s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef	struct		s_arg
{
	int				i;
	int				in;
	int				end;
}					t_arg;

t_arg				g_arg;
t_env				*g_env;
int					(*g_builtins[7])(int, int, char **);
char				*g_builtins_str[8];

int					cparser(char *s, char q);
int					ft_prompt(char **line);
int					check_syntax(char *s);
char				*check_line(char *line);
int					have_end(char *s, char quote, int *start);
char				**parser_split(char *line, char c);
char				*env_to_str(char *line);
void				init_shell(char **env);
bool				handle_return(int rt, char *line);
t_pipeline			**parse_data(char *line);
void				exec_parsed(t_pipeline **parsed_line);
char				*inside_quotes(char *s, int *start, char quote);
char				*outside_quotes(char *s, int *start);
t_pipeline			**parser(char *line);
char				**fml_parser(char *line);
int					check_arg(char *s);
char				*get_arg(char *line, char c, int *pos);
t_redir				get_tokens(char *s);
char				*append(char *s, char c);
int					quotes_attached(char *s);
void				print_parsed_line(t_pipeline **parsed_line);
char				*get_command(char *line);
t_command			*new_cmd(char *line);
void				free_cmds(t_command **cmd);
void				free_pipeline(t_pipeline **p);
int					tab_len(char **tab);
int					exists_in_tab(char *s, char **tab);
int					index_of_in_tab(char *s, char **tab);
int					free_s_tab(char **tab);
void				*free_and_return(void *ptr, void *ret);
int					string_equal(char *s1, char *s2);
int					is_blank(char c);
void				init_environment(char **envp);
int					get_env_len();
t_env				*new_env(char *key, char *value);
void				set_env(char *key, char *value);
void				unset_env(char *key);
t_env				*env_at_index(int index);
t_env				*env_with_key(char *key);
char				**get_env_tab();
void				free_env(void);
void				free_one_env(t_env *e);
void				init_builtins();
int					builtin_echo(int in, int out, char **argv);
int					builtin_pwd(int in, int out, char **argv);
int					builtin_cd(int in, int out, char **argv);
int					builtin_exit(int in, int out, char **argv);
int					builtin_env(int in, int out, char **argv);
int					builtin_export(int in, int out, char **argv);
int					builtin_unset(int in, int out, char **argv);
char				**get_parsed_path(void);
int					find_file_in_path(char **absolute_path, char *cmd);
void				redirect_in_out(int in, int out);
void				queue_pid(int pid);
int					new_builtin_process(int in, int out,
						char **argv, int(*builtin)(int, int, char **));
int					new_process(int in, int out, char **cmd, int *status);
int					execute_command(int in, int out, char **argv);
int					redirect_inputs(char **tokens,
						int out, int pipe_in, char **inputs);
int					redirect_outputs(t_command *cmd, int pipe_in, int pipe_out);
int					execute_pipeline(t_pipeline *pipeline);
void				signal_handler(int signal);
char				*dollar_norm_dollar(char *s, int *i, char *line);
char				*dollar_norm(char *s, int *i, int value);
char				*get_norm_outside(int *i, char *m, char *s, int *start);
char				*get_norm_inside(int *i, char *s, char *rt);
char				*env_normed(char *s, char *line, int *i);
char				*handle_env(char *line, int *pos);
int					check_arg(char *s);
void				norm_quote(char *s, int *i, int *in, int *end);
void				check_inc_arg(char *s, int *i, int *in);
void				norm_quote(char *s, int *i, int *in, int *end);
int					ft_strsearch(char *s, char n);
int					has_redir(char *s, int *pos);
int					check_pipeline(char *s);
int					check_quotes(char *s, int *pos);
int					check_pipe(char *s);
int					check_redir(char *s);
int					has_redir(char *s, int *pos);
int					no_alpha(char *s);
int					quote_ends(char *s, char c);
void				quote_token(char *s, int *i, t_redir *redir);
void				fill_redir(t_redir *redir, char *s, int *i, int in);
char				**realloc__(char **s, char *t);
char				*get_rarg(char *line, int *pos);
char				*rarg_fill_norm(char *s, char *line, int *i);
void				init_redir(t_redir *redir);
void				inc_(int *i, char *s);
void				rarg_norm(char *line, int *i, int *end, int *in);
char				*get_inside(char *s, int *start, char quote);
#endif
