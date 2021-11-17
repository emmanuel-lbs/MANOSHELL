#include "../../includes/minishell.h"

int	parsing(char *str, t_struct *s)
{
	if (command_syntax(str) == -1)
		return (-1);
	printf("nb de token = %d\n",ft_countwords(str));
//	if (shell_split(str, s) == -1)
//		return (-1);
	return (0);
}

/*
 * params	: la commande qui viens d'etre taper + la struct principal
 * return	: -1 si erreur, 0 si tout est ok
 * def		:	cree chainlst de char** de toutes les commande
 *				check toutes les erros possibles de chaques char **
 *
 */
