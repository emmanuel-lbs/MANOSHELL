#include "../../includes/minishell.h"

int	parsing(char *str, t_struct *s)
{
	char **tokeniser;

	if (no_commande(str) == -1)
		return (-1);
	if (command_syntax(str) == -1)
		return (-1);
	tokeniser = split_shell(str, s);
	if (tokeniser == NULL)
		return (-1);
	s->bob = create_bob(tokeniser);
	s->first_bob = s->bob;
	ft_free_double_char(tokeniser);
	return (0);
}

