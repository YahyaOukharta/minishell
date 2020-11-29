#include "minishell.h"

// to do list xD 3yiit

char         *check_line(char *line)
{
    // check Syntax
    if (check_syntax(line) == NULL)
        return (NULL);
    return (line);
}

