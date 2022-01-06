#include "../../includes/minishell.h"

int	is_builtin(t_struct *s)
{
	if (strcmp(s->bob->token[0], "cd") == 0)
		ft_cd(s);
	else if (ft_strcmp(s->bob->token[0], "echo") == 0)
		ft_echo(s);
	else if (strcmp(s->bob->token[0], "pwd") == 0)
		ft_pwd();
	else if (strcmp(s->bob->token[0], "export") == 0)
		ft_export(s);
	else if (strcmp(s->bob->token[0], "unset") == 0)
		ft_unset(s);
	else if (strcmp(s->bob->token[0], "env") == 0)
		ft_env(s);
	/*else if (strcmp(s->bob->token[0], "exit") == 0)
		ft_cd(s);*/
	else
		return (0);
	return (1);
}
