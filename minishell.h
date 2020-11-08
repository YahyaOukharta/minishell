#ifndef MINISHELL_H
# define MINISHELL_H
# include "ft_printf/ft_printf.h" 
# include "gnl/get_next_line.h"
# include <stdbool.h>

# define STDOUT 1
# define STDIN  0
# define STDERR 2

# define QUOTE(x)   (x == '\'' || x == '\"') ? 1 : 0

typedef struct  s_command
{
    char        *tokens;
    char        **input_files;
    char        **output_files; 
}               t_command;

typedef struct  s_pipeline
{
    t_command*  cmds;
}               t_pipeline;                 //parser returns (t_pipeline* parsed_line)

// Here any utility function we need 

int     tab_len(char **tab);                //get len of array of strings

// Environment

typedef struct      s_env
{
    char            *key; 
    char            *value;
    struct s_env    *next;
}                   t_env;

t_env               *g_env;                 //Environment global variable

int     status;                             // main loop status

int         ft_prompt(char *msg, char **line); // prompt user to input 
char        *check_syntax(char *s);             // check input syntax
void        init_environment(char **envp);      //Get all envs from extern char *environ[] // push them to linked list

int     get_env_len();   // get number of env vars
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

char	**get_parsed_path(void);                    // split $PATH,':'
int		find_file_in_path(char **absolute_path, char *cmd); // find pseudo in structure.md

// dup2() wrapper

void    redirect_in_out(int in, int out);           // only redirect stdin if in != 0   // only redirect stdout if out != 1  

// Spawning processes functions

int     new_builtin_process(int in, int out,char **argv, int(*builtin)(int,int, char **));
int     new_process(int in, int out, char **cmd, int *status);
int     execute_command(int in, int out, char **argv); 

// Redirections

int redirect_inputs(char **cmd_tokens, int pipe_in, int out, char **inputs);
int  redirect_outputs(int pipe_in, int pipe_out, t_command *cmd); 

// Pipeline

int execute_pipeline(t_pipeline *pipeline); 

#endif