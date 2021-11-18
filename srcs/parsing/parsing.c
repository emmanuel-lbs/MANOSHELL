#include "../../includes/minishell.h"

int	no_commande(char *str)
{
	int i;

	i = 0;
	if (str[i] == 0)
		return (-1);
	while (str[i])
	{
		if (str[i] != ' ')
			return (0);
		i++;
	}
	return (-1);
}

int	parsing(char *str, t_struct *s)
{
	if (no_commande(str) == -1)
		return (-1);
	if (command_syntax(str) == -1)
		return (-1);
	printf("nb de token = %d\n", ft_countwords(str));
//	if (shell_split(str, s) == -1)
//		return (-1);
	pre_split(str);
	return (0);
}

/*
 * params	: la commande qui viens d'etre taper + la struct principal
 * return	: -1 si erreur, 0 si tout est ok
 * def		:	cree chainlst de char** de toutes les commande
 *				check toutes les erros possibles de chaques char **
 *
 */
