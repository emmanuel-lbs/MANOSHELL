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
/*
 * params	: la commande qui viens d'etre taper
 * return	: -1 si erreur, 0 si tout est ok
 * def		: check si ligne vide
 */

char	*malloc_cut_cmd(char *str, int i)
{
	char *cmd;
	int j;

	j = i;
	while (str[i] && str[i] != '|')
	{
		if (str[i] == '\'' || str[i] == '\"' )
			skip_quote(str, str[i], &i);
		(i)++;
	}
	j = (i) - j;
	cmd = malloc(sizeof(char) * (j + 1));
	return (cmd);
}

int		cpy_quote(char *cpy, char *cmd, char quote, int *j)
{
	int i;

	i = 0;
	cpy[*j] = quote;
	(*j)++;
	while (cmd[i] && cmd[i] != quote)
	{
		cpy[*j] = cmd[i];
		(*j)++;
		i++;
	}
	return (i);
}

char *cut_cmd(char *str, int *i)
{
	char	*cmd;
	int		j;

	cmd = malloc_cut_cmd(str, *i);
	j = 0;
	while (str[*i] && str[*i] != '|')
	{
		if (str[*i] == '\'' || str[*i] == '\"')
		{
			cpy_quote(cmd, str, str[*i], &j);
		}
		cmd[j] = str[*i];
		(*i)++;
		j++;
	}
	cmd[j] = 0;
	(*i)++;
	return (cmd);
}
/*
 * params	: l'input entiere, et l'index du caract ou je commence
 * return	: une commande
 * def		: vas cut l'input pour ne garder que une commande
 *			  (fct modifie en meme temps l'index pour qu'au prochain appel
 *			  je redemare la ou je me suis arreter)
 *			  ex : echo a b >> lol | wc -l mano | oe;
 *			  return ("echo a b >> lol")
 */

char **test(void)
{
	char **oui;

	oui = malloc(sizeof(char *) * 3);
	oui[0] = malloc(sizeof(char) * 10);
	oui[1] = malloc(sizeof(char) * 10);
	oui[2] = 0;
	oui[0] = "salut\0";
	oui[1] = "MANOOO\0";
	return (oui);
}

int	create_bob(t_struct *s, char *str)
{
	int		i;
	char	*cmd;
	int j;

	i = 0;
//	cmd = cut_cmd(str , &i);
	printf("la commmande -> %snb de token = %d\n", str, ft_countwords(cmd));
//	s->bob.token = split_shell(cmd);;
//	j = 0;
//	while (s->bob.token[j])
//	{
//		printf("%s\n", s->bob.token[j]);
//		j++;
//	}
//	new_block(cmd);
//	while (str[i])
//	{
//		free(cmd);
//		cmd = cut_cmd(str , &i);
//		printf("la commmande -> %snb de token = %d\n",cmd, ft_countwords(cmd));
//		s->bob.token = split_shell(cmd);;
//		j = 0;
//		while (s->bob.token[j])
//		{
//			printf("%s\n", s->bob.token[j]);
//			j++;
//		}
//		//		add_back_bob(&s->bob.next, new_block(cmd));
//	}
//	return (0);
}
/*
 * params	: la struct et l'input taper
 * return	: je sais pas encore/////////////////////////////////////////////////////////
 * def		: cree la liste chainer comportant les cmd de char ** les fd;
 */

int	parsing(char *str, t_struct *s)
{
	if (no_commande(str) == -1)
		return (-1);
	if (command_syntax(str) == -1)
		return (-1);
//	printf("ok\n\n");
//		if (create_bob(s, str) == -1)
//			return (-1);
	return (0);
}

/*
 * params	: la commande qui viens d'etre taper + la struct principal
 * return	: -1 si erreur, 0 si tout est ok
 * def		:	cree chainlst de char** de toutes les commande
 *				check toutes les erros possibles de chaques char **
 *
 */
