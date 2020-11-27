# shell structure

  `ls -l > out | grep "Desk" < out | base64 ; echo "hello world"`

# Interpreter   
 * Environment:
    - Expand $? $ENV_VAR first

 * Spliting into commands and tokens 
    - Using split functions that respect quotes { '12 | qwerty ;' } {  abc"12 456" }

        - Get separate commands : split ; 
        - Split into pipeline : split |
        - Get inputs and outputs in order : 
            { "< input_file" }  { "> output_file" } { ">> output_file" }
        - Output file names include the redirection sign, so we can know if we should truncate or not
        - input file names shouldn't include the redirection sign
    ## single command structure :
        
        typedef struct s_command
        {
            char **tokens;
            char **input_files;
            char **output_files; 

        }   t_command;

    ## pipeline structure :

        typedef struct s_pipeline
        {
            t_command** cmds;
            int n_commands;

        }   t_pipeline;

    ## line structure ( Everything the user types before hitting Enter) :

        t_pipeline **parsed_line;


# Executer

 * Execute pipeline :
    -   first command of the pipeline reads from stdin
    -   last command writes on stdout, unless it has an output specified, ex : ls | grep 'Desktop' > output_file
    -    all commands are executed reading from every input available and writing to all ouputs available ..
     ls | grep "desktop" < in1 < in2 > out1 > out2 | cat
     order of execution of grep : 
        - read from pipe_in write to out1
        - read from pipe_in write to out2
        - read from pipe_in write to pipe_out
        - read from in1 write to out1
        - read from in1 write to out2
        - read from in1 write to pipe_out
        - read from in2 write to out1
        - read from in2 write to out2
        - read from in2 write to pipe_out

        ```
        for each input in inputs:
            for each output in outputs:
                execute_cmd(cmd, input, output); ####
        ```

        ```
        for each output in outputs:
            for each input in inputs:
                execute_cmd(cmd, input, output); 
          #### This is what we're gonna do, 
          ### this is better because we will open the output files only once nd we will read from every input and append
        ```
    -  do this for each pipeline in parsed_line

 * Execute command :
    - returns status, error code, stored in global g_status
    - takes input and output fd
    - is the command a builtin ? 
        if so, execute in child process, to allow output redirection, (only for env, echo, pwd, builtins that produce an output, maybe this should be the case for every builtin, error messages should be redirectable, error msgs are normally logged on stderr ...)
    - is the command not a builtin ?
        - create child process,
        - check if the file exists using fstat:
            - if filename contains "/" : means absolute path, fstat(fname)
            - else try to find in $PATH
        - redirect output and input using dup2, only if in!= 0 and out!=1
        - execute command 

######

# Minishell components 

## Environment :

 * Environment variables will be stored in a linked list / hashtable in global variable g_env: 
    
    ``` 
        typedef struct      s_env
        {
            char            *key; 
            char            *value;
            struct s_env    *next;
        }                   t_env;

        t_env *g_env;
    ```

 * Functions:
    
    ``` 
        void    init_environment(char **envp);     
            //Get all envs from extern char *environ[] // push them to linked list
        
        t_env   *env_at_index(int index); //NULL if out of bounds
        t_env   *env_with_key(char *key); //NULL if not found
        
        int get_env_len(); // get number of env vars

        void    set_env(char *key, char *value);
            //add new variable if doesnt exist // else updates value
        void    unset_env(char *key);
            //removes variable if exists // else does nothing 

        t_env   *new_env(char *key, char *value); // used by set_env()
        
        char	**get_env_tab(); //returns environment as array of strings ("KEY=VALUE")
    ```

## Builtins :

 * Builtins will be stored in a global array of functions:

    ```
        int (*g_builtins[7])(int, int, char **);
            //Array of the seven builtin commands

        char    *g_builtins_str[8]; 
            // Array of strings for each command name , + 1 for null terminating the array
    ```

 * Functions :

    - All builtin functions take as a parameter an input and an output file descriptor to allow I/O redirection.
    - We only care here about pwd, env and echo because they're the only builtins that produce an output, so we might want to redirect that output
    - the exit builtin in contrast shouldnt be executed in a child process, since it should exit(0) on the main process
    - The functions also take as an argument an array of the cmd tokens, ie : {"echo","hello","world","\0"}
    - The functions return a status code which will be stored in global variable g_status 

    ```
        void    init_builtins();
            // initializes g_builtins with each of these functions

        int     builtin_echo(int in, int out, char **argv); //**
        int     builtin_pwd(int in, int out, char **argv);  //**  //getcwd() // care for $PWD
        int     builtin_cd(int in, int out, char **argv);   //chdir() // care for $HOME
        int     builtin_exit(int in, int out, char **argv); //exits shell

            // Environmemt functions
        int     builtin_env(int in, int out, char **argv);  //**
        int     builtin_export(int in, int out, char **argv);
        int     builtin_unset(int in, int out, char **argv);

        // ** output must be redirectable
    ```

## $PATH

  - The $PATH environment variable is used to locate executables accross the file system so only the file name is typed in the shell and not the whole path.
  * Two functions will come useful:
    
    ```
        char	**get_parsed_path(void); // from string to array paths

        int		find_file_in_path(char **absolute_path, char *cmd); 
            // takes as parameters a pointer to a string where the absolute path will be stored and the command we're trying to find;
            // if file is found, its absolute path is stored in *absolute_path
            // returns 1 if finds file, else 0
            // if file name is absolute path (contains '/'), use stat() to find file and return
            // else loop over parsed path, and stat(), return 0 if never found 
    ```
## 'dup2()' Redirecting I/O :

  - To allow input/output redirection from/to a file, we must duplicate the target so that reading/writing on stdin or stdout redirects to that filedescriptor.
  - ``` dup2(some_file_descriptor , STDIN); ``` After executing this function, everytime we read from STDIN, we're actually reading from ``` some_file_descriptor ```
  - ``` man dup2 ``` RTFM
  - We'll write a function that takes two file descriptors, an input and an output, and redirects I/O accordingly

  * Functions:

  ```
        void    redirect_in_out(int in, int out);
            // only redirect stdin if in != 0   
            // only redirect stdout if out != 1  
  ```

## Fork, Execve: Spawning processes :

### Spawning builtin processes:

  - For that we'll use a function that starts a child process and executes the specified builtin
  - This function takes as an argument two file descriptors (in and out), the command's arguments ```char **argv``` (including command name), and a pointer to the builtin function.
  - The function returns the return value from ```int builtin(int,int,char **)```

    ```
        int new_builtin_process(int in, int out,char **argv, int(*builtin)(int,int, char **));
    ```

  - **IMPORTANT** : Only echo, pwd and env should be executed in a child process, to be able to redirect their output, exit should be executed in main process 

### Spawning processes for executables:

  - We'll use this function, just like builtin processes, it takes two file descriptors and all the command's arguments, plus a pointer to ```g_status``` global variable:

    ```
        int new_process(int in, int out, char **cmd, int *status);
    ```

  - Creates a child process
  - Looks for file in path using ```find_file_in_path()```, if not found, print error message, return 127
  - If file is found, redirect I/O then execute using ```execve()```
  - If ```execve()``` returns -1, it means that we do not have permissions to execute that file, print error message and return 126
  - Else wait for process to terminate and store its status in ```*status```, and return it
  - **NOTE** : ```execve()``` takes as a third parameter an environment array, we can get that using ```get_env_tab()```

### Execute any command:
  
  - Function:
  ```
        int	execute_command(int in, int out, char **argv);
            // Is the command a builtin ? 
                // Find out by comparing with the values `g_builtins_str`
                    // If the name matches, 
                    // Get the index and execute `new_builtin_process()`
                    // Give it as third argument `g_builtins[index]`
                // Else execute `new_process()`
            // Sets g_status as the return of the executed processe
            // Returns g_status
  ```

## Redirections ( < , > , >>)
  
- **When reading from the input fds, `pipe_in` always comes before the other files.**
- **When writing to the outputs, `pipe_out` always comes last.**
  
###  **IMPORTANT**

  ------------------------------------------------------------ 


  - For example, consider ` grep < in1 < in2 | cat `, to execute the first command of this pipeline, we have to execute the command for each input and for each output.
  - The outputs in this case are only `pipe_out`, which could be STDOUT or the file descriptor from the writing end of the pipe.
  - The inputs are, in this order: `pipe_in` (which is STDIN), `in1` and `in2`
  - **This command will not read from STDIN**

  ------------------------------------------------------------ 

  - For example, consider ` ls | grep 'keyword' > out1 > out2  `, to execute the last command of this pipeline, we have to execute the command for each input and for each output (in this order).
  - The inputs in this case are only `pipe_in`, which could be STDIN or the file descriptor from the reading end of the pipe.
  - The outputs are, in this order: `out1` , `out2` and `pipe_out` (which is STDOUT)
  - **This command will not write to STDOUT**

  ------------------------------------------------------------ 

### redirect_inputs()


  - Function:

    ```
        int redirect_inputs(char **cmd_tokens, int pipe_in, int out, char **input_files);
    ``` 

  - So we will write a function that executes the command while
  reading from every input we have and writing to a single output fd, which we will launch in loop later for every output we have.
  - This function takes as parameters the command tokens, the `pipe_in` fd, since it is always read from first, an output file descriptor, and the array of input files' names.
  - It executes the command using `execute_command()` we wrote earlier.
  - **NOTE** : Consider `grep < input_file`, this command wont read from STDIN because it has an input file specified, this case only concerns first command in a pipeline.
  - We first execute the command reading from `pipe_in` but only if it is not the first command and doesnt have any input file specified (only if `!(pipe_in == 0 && tab_len(inputs) != 0)`)
  - Then we loop over the inputs array:
     - We open the file using `open()`, if it fails to open we print an error message and return 1
     - We execute the command reading from the file we opened and then we close it
     - `execute_command()`'s return value is always stored in `g_status`
     - We close the file
  - After the loop is over, return `g_status`
  
  - **memo** : Maybe inputs dont need to be stored as `"< fname"`

### redirect_outputs()

  - Function :

    ```
        int  redirect_outputs(int pipe_in, int pipe_out, t_command *cmd);
    ```

  - This function will take care of executing the command with the right output file descriptors.
  - It will call `redirect_inputs()` for each output file, plus `pipe_out`.

  - it will first loop over the output files array (`cmd->output_files`):
    - Remove the `> >>` redirection signs, and store those in variable because the way the files are opened depend on them
    - Open the file:
        - Allow file creation if doesnt exist
        - Write only
        - Enable appending to the end of the file, because `redirect_inputs()` will write on the file, for each execution (for each input)
        - Truncate the file only if the stored redirection sign is `>`
        - Make sure the file is opened/created with the right permissions, (reproduce on bash and compare)
    - Execute `redirect_inputs()`, passing it the file descriptor we just opened as third argument, and store its return in `g_status`
    - Its arguments would be: `(cmd->tokens, pipe_in, the_fd_we_just_opened, cmd->input_files)`
    - Close the file

  - **NOTE** : 
   - Consider `ls | grep 'something' > out1 > out2`, in this case we will not output anything to `pipe_out`, which would be STDOUT, because it is the last command and it has output files.
   - Which means a command doesnt output to `pipe_out` if the command is the last in the pipeline and the are output files specified

  - Then we have to write to `pipe_out`, to do that we execute `redirect_inputs()` again, but this time only if `!(pipe_out == 1 && tab_len(cmd->output_files) > 0)`; once again storing its return value in `g_status`.
  - Return `g_status`

## Pipeline, Oahu:

  - To execute a pipeline, we will loop over the commands, and execute them in order while redirecting one command's output to the next's output.
  - The key here is that, the first command of the pipeline always reads from STDIN, and the last always writes to STDOUT, **UNLESS ONE OF THE CONDITIONS CITED ABOVE ARE TRUE**
  - We will use the `pipe()` system call, which takes an `int fd[2]`, and allocates two file descriptor

  - After executing : ``` int fd[2];   pipe(fd); ```:
    **What is written on `fd[1]`, can be read from `fd[0]`**

  - Function :
    
    ```
        int execute_pipeline(t_pipeline *pipeline); 
         // access command using pipeline->cmds[i]
    ```

  - This function will iterate over the commands in the pipeline and execute them in order while passing them the right file descriptor depending on their position in the pipeline.
  - This can be done in many ways.
  - One way would be to :
    - `N` is number of commands in the pipeline
    - create two variables `int in,out;`
    - Initialize `in` with zero, since the first command has to read from STDIN
    - iterate over `N-1` commands :
        - Initialize pipe using `pipe`
        - set `out` as `fd[1]` (at this point in the first iteration, `in` would be STDIN, and `out` would be `fd[1]`)
        - Execute the command using `redirect_outputs()`, passing it `in` and `out` and the command object as arguments.
        - close `fd[1]` for some reason ?????? (`fd[0]` needs to be closed too, i suppose we should close it in the `redirect_in_out()` function ..? )
        - set `in` as `fd[0]`, so that in the next iteration the command reads from the pipe what has been written in the previous iteration
    - When loop is over, only the last command is left.
    - Set `out` to 1, since the last command will output to STDOUT
    - `in` is already set to the reading end of the pipe, where we will read what the N-1 command has written
    - execute the command, once again using `redirect_outputs()`, passing it the same arguments
    - **Always store `redirect_outputs()`'s return in `g_status` (this should be a habit by now)**

## The main function (finally):

### Global variables:

  - Summary of all the global variables we'll need :

    ```
        extern char **environ; // where the inherited environment is stored

        int	g_status; // where the status of the last executed command will always be stored

        int (*g_builtins[7])(int, int, char **); // where builtin functions are stored
        char *g_builtins_str[8]; // where builtin functions' names are stored, for comparison with user input
    ```
### Init:

  - Before launching the main loop, we initialize the Environment, and the builtins functions:

    ```
        init_environment(environ);
        init_builtins();
    ```
  - Maybe init the parser too ?

### Main loop:

  - Loop while `g_status > -1`:
    - Print the prompt
    - Read line using `get_next_line`
    - Parse line using parser to get `t_pipeline **parsed_line`, which would be an array of pipelines.
    - Loop over pipelines, execute them using `execute_pipeline`.
  - Return (0)