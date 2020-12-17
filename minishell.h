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
// # include <term.h>
// # include <curses.h>
# include <stdio.h>

# define STDOUT 1
# define STDIN  0
# define STDERR 2

# define QUOTE(x)   (x == '\'' || x == '\"') ? 1 : 0

# define max(a , b) (a > b ? a : b)
# define min(a , b) (a < b ? a : b)

int     g_status;                             // main loop status
int     signal_c;                            // ctrl -c
int     signal_d;                           // ctrl-D
pid_t   g_child;                           // get pid to kill procces on Sigquit

typedef struct  s_command
{
    char        **tokens;
    char        **input_files;
    char        **output_files; 
}               t_command;

typedef struct  s_pipeline
{
    t_command**  cmds;
    int n_commands;
}               t_pipeline;                 //parser returns (t_pipeline* parsed_line)

// Here any utility function we need 

int                 ft_prompt(char *msg, char **line);   // prompt user to input 
char                *check_syntax(char *s);             // check input syntax
char                *check_line(char *line);           // Fix imput ;=
int			        have_end(char *s, char quote, int *start);
char	            **parser_split(char *line, char c);
char                *env_to_str(char *line);        // Get $var value

// Parser

typedef struct  s_redir
{
    char        **ins;
    char        **outs;
    char        **tokens;
}               t_redir;

char        *inside_quotes(char *s, int *start, char quote);
char        *outside_quotes(char *s, int *start);
t_pipeline  **parser(char *line);
char		**fml_parser(char *line);
int			check_arg(char *s);
char	    *get_arg(char *line, char c, int *pos);
t_redir     get_tokens(char *s);
char	    *append(char *s, char c);
int			quotes_attached(char *s);


//miniparser utils

void        print_parsed_line(t_pipeline **parsed_line);

char        *get_command(char *line);
t_command   *new_cmd(char *line);
int         tab_len(char **tab);
int         exists_in_tab(char *s, char **tab);
int         index_of_in_tab(char *s, char **tab);
int         free_s_tab(char **tab);
void        *free_and_return(void *ptr, void *ret);
int         string_equal(char *s1, char *s2);
int         is_blank(char c);

// Environment

typedef struct      s_env
{
    char            *key; 
    char            *value;
    struct s_env    *next;
}                   t_env;

t_env               *g_env;                 //Environment global variable

void        init_environment(char **envp);      //Get all envs from extern char *environ[] // push them to linked list

int     get_env_len();                      // get number of env vars
t_env   *new_env(char *key, char *value);   // used by set_env()
void    set_env(char *key, char *value);    //add new variable if doesnt exist // else updates value
void    unset_env(char *key);               //removes variable if exists // else does nothing 
t_env   *env_at_index(int index);           //NULL if out of bounds
t_env   *env_with_key(char *key);           //NULL if not found
char	**get_env_tab();                    //returns environment as array of strings ("KEY=VALUE")

// Builtins 

int     (*g_builtins[7])(int, int, char **);        //Array of the seven builtin commands
char    *g_builtins_str[8];                         //Array of strings for each command name , + 1 for null terminating the array

void    init_builtins();                            // initializes g_builtins with each of these functions

int     builtin_echo(int in, int out, char **argv); //**
int     builtin_pwd(int in, int out, char **argv);  //**  //getcwd() // care for $PWD
int     builtin_cd(int in, int out, char **argv);   //chdir() // care for $HOME
int     builtin_exit(int in, int out, char **argv); //exits shell

    // Environmemt builtins

int     builtin_env(int in, int out, char **argv);  //** prints get_env_tab()'s content
int     builtin_export(int in, int out, char **argv);
int     builtin_unset(int in, int out, char **argv);

// $PATH functions

char    **get_parsed_path(void);                    // split $PATH,':'
int     find_file_in_path(char **absolute_path, char *cmd); // find pseudo in structure.md

// dup2() wrapper

void    redirect_in_out(int in, int out);           // only redirect stdin if in != 0   // only redirect stdout if out != 1  

// Spawning processes functions

int     new_builtin_process(int in, int out,char **argv, int(*builtin)(int,int, char **));
int     new_process(int in, int out, char **cmd, int *status);
int     execute_command(int in, int out, char **argv); 

// Redirections

int     redirect_inputs(char **tokens, int out, int pipe_in, char **inputs);
int     redirect_outputs(t_command *cmd, int pipe_in, int pipe_out); 

// Pipeline

int     execute_pipeline(t_pipeline *pipeline); 

// Signals

void    signal_handler(int signal);

#endif