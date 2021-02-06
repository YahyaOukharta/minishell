# Minishell
> As beautiful as a shell

## Requirements

* gcc 
* make

## Usage

```sh
make
./minishell
```

## Features

* Builtins : ``` echo cd pwd env export unset exit ```
* Redirections : ``` cat < in >> out ```
* Pipes
* Simple and double quotes
* Backslash
* Environment variables : ``` echo $PATH ```
* Search in PATH for binaries
* ctrl-c ctrl-d ctrl-\

## Ressources

_For a small documentation of our minishell, please refer to the [Wiki][wiki]._

* https://brennan.io/2015/01/16/write-a-shell-in-c/
* https://stackoverflow.com/questions/8082932/connecting-n-commands-with-pipes-in-a-shell
* man ``` write, open, read, close, fork, wait, waitpid, wait3, wait4, signal, kill, exit, getcwd, chdir, stat, lstat, fstat, execve, dup, dup2, pipe, opendir, readdir, closedir, strerror, errno ```

## Authors

Yahya Oukharta – https://github.com/YahyaOukharta
Mohamed Alaoui – https://github.com/
