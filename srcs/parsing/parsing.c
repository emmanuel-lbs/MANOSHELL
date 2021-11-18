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

	//choisie
	int i;
	char *cmd;

	i = cut_word(&cmd, str);
	s->lst = lst_new(new_block(cmd));
	while (str[i])
	{
		free(cmd);
		i = cut_cmd(&cmd, &str[i]);
		lst_add_back(s->lst, ft_lstnew(new_block(cmd)));
	}
	free(cmd);


	//ou
	create_bob(s, cmd);

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
