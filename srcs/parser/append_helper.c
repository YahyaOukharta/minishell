#include "minishell.h"

char		*append_n(char *s, char *line, int *i, int n)
{
	char	*t;

	t = NULL;
	while (n--)
	{
		t = append(s, line[*i]);
		*i += 1;
		t = append(s, line[*i]);
		*i += 1;
	}
	return (t);
}