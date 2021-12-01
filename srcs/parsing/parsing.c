#include "../../includes/minishell.h"

int	parsing(char *str, t_struct *s)
{
		char **tokeniser;

		if (no_commande(str) == -1)
				return (-1);
		if (command_syntax(str) == -1)
				return (-1);
		tokeniser = split_shell(str);
		if (tokeniser == NULL)
				return (-1);
		int i = 0;
		while(tokeniser[i])
		{
				printf("%s\n",tokeniser[i]);
				i++;
		}
//		if (create_bob(s, tokeniser) == -1)
//				return (-1);
		return (0);
}

