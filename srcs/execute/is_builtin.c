#include "../../includes/minishell.h"

int	is_builtin(t_struct *s)
{
	if (ft_strcmp(s->bob->token[0], "echo") == 0)
		ft_echo(s);
	else if (strcmp(s->bob->token[0], "pwd") == 0)
		ft_pwd();
	/*else if (strcmp(s->bob->token[0], "export"))
		ft_cd(s);
	else if (strcmp(s->bob->token[0], "unset"))
		ft_cd(s);
	else if (strcmp(s->bob->token[0], "env"))
		ft_cd(s);
	else if (strcmp(s->bob->token[0], "exit"))
		ft_cd(s);*/
	else
		return (0);
	return (1);
}
