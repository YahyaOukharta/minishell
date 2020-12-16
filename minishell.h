#ifndef MINISHELL_H
# define MINISHELL_H
# include "ft_printf/ft_printf.h" 
# include "gnl/get_next_line.h"
# include <stdbool.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <signal.h>
# define STDOUT 1
# define STDIN  0
# define STDERR 2
# define QUOTE(x)   (x == '\'' || x == '\"') ? 1 : 0
# define MAX(a , b) (a > b ? a : b)
# define min(a , b) (a < b ? a : b)

int					g_status;
int					signal_c;
int					signal_d;
pid_t				g_child;

typedef struct		s_command
{
	char			**tokens;
	char			**input_files;
	char			**output_files;
}					t_command;

typedef struct		s_pipeline
{
	t_command**		cmds;
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

t_env				*g_env;
int					ft_prompt(char *msg, char **line);
char				*check_syntax(char *s);
char				*check_line(char *line);
int					have_end(char *s, char quote, int *start);
char				**parser_split(char *line, char c);
char				*env_to_str(char *line);
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
int					(*g_builtins[7])(int, int, char **);
char				*g_builtins_str[8];
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
int					new_builtin(int in, int out,char **av, int(*b)(int,int, char **));
int					new_process(int in, int out, char **cmd, int *status);
int					execute_command(int in, int out, char **argv);
int					redirect_inputs(char **av, int out, int pipe_in, char **in_f);
int					redirect_outputs(t_command *cmd, int pipe_in, int pipe_out);
int					execute_pipeline(t_pipeline *pipeline);
void				signal_handler(int signal);

#endif