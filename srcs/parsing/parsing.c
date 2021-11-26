#include "../../includes/minishell.h"

char	*malloc_cut_cmd(char *str, int i)
{
		char *cmd;
		int j;

		j = i;
		while (str[i] && str[i] != '|')
		{
				if (str[i] == '\'' || str[i] == '\"' )
						skip_quote(str, str[i], &i);
				if (str[i] && ft_is_quote(str[i]) == 0)
						(i)++;
		}
		j = (i) - j;
		//fct dis il y as cmb de caractere quote pour soustraire a j;
		cmd = malloc(sizeof(char) * (j + 1));
		return (cmd);
}

void		cpy_quote(char *cpy, char *str, int *cpy_i, int *str_i)
{
		char	quote;

		quote = str[*str_i];
		(*str_i)++;
		while (str[*str_i] && str[*str_i] != quote)
		{
				cpy[*cpy_i] = str[*str_i];
				(*cpy_i)++;
				(*str_i)++;
		}
		(*str_i)++;
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
char *cut_cmd(char *str, int *str_i)
{
		char	*cmd;
		int		cmd_j;
		int		tmp;

		tmp = *str_i;
		cmd = malloc_cut_cmd(str, tmp);
		int i = 0;
		while (str[i] && str[i] != '|')
		{
				cmd[i] = 'a';
				i++;
		}
		cmd[i] = 0;

		cmd_j = 0;
		while (str[tmp] && str[tmp] != '|')
		{
				if (ft_is_quote(str[tmp] == 1))
						cpy_quote(cmd, str, &cmd_j, &tmp);
				if (str[tmp] && ft_is_quote(str[tmp]) == 0)
				{
						cmd[cmd_j] = str[tmp];
						tmp++;
						cmd_j++;
				}
		}
		cmd[cmd_j] = 0;
		*str_i = tmp;
		return (cmd);

		//while (str[*str_i] && str[*str_i] != '|')
		//{
		//	if (ft_is_quote(str[str_i]) == 1)
		//		cpy_quote(cmd, str, &str_i, &cmd_j);
		//	if (str[str_i] && ft_is_quote(str[str_i]) == 0)
		//		(str_i)++;
		//	cmd[cmd_j] = str[*str_i];
		//	(*str_i)++;
		//	cmd_j++;
		//}
		//cmd[cmd_j] = 0;
		//(*str_i)++;
		return (cmd);
}

/*
 * params	: la struct et l'input taper
 * return	: je sais pas encore/////////////////////////////////////////////////////////
 * def		: cree la liste chainer comportant les cmd de char ** les fd;
 */
int	create_bob(t_struct *s, char *str)
{
		int		i;
		char	*cmd;
		int j;

		i = 0;
		cmd = cut_cmd(str , &i);
		printf("%s\n",cmd);
		//	printf("la commmande -> %snb de token = %d\n", str, ft_countwords(cmd));
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
		return (0);
}

/*
 * params	: la commande qui viens d'etre taper + la struct principal
 * return	: -1 si erreur, 0 si tout est ok
 * def		:	cree chainlst de char** de toutes les commande
 *				check toutes les erros possibles de chaques char **
 *
 */
int	parsing(char *str, t_struct *s)
{
		if (no_commande(str) == -1)
				return (-1);
		if (command_syntax(str) == -1)
				return (-1);
//		if (create_bob(s, str) == -1)
//				return (-1);
		return (0);
}

