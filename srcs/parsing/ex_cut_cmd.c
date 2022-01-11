
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

char	*cpy_quote(char *cpy, char *str, int *cpy_i, int *str_i)
{
		char	quote;

		quote = str[*str_i];
		cpy[*cpy_i] = str[*str_i];
		(*cpy_i)++;
		(*str_i)++;
		while (str[*str_i] && str[*str_i] != quote)
		{
				cpy[*cpy_i] = str[*str_i];
				(*cpy_i)++;
				(*str_i)++;
		}
		cpy[*cpy_i] = str[*str_i];
		(*cpy_i)++;
		(*str_i)++;
		return (cpy);
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
		cmd_j = 0;
		cmd = malloc_cut_cmd(str, tmp);
		while (str[tmp] && str[tmp] != '|')
		{
				if (ft_is_quote(str[tmp]) == 1)
						cmd = cpy_quote(cmd, str, &cmd_j, &tmp);
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
}


/*
 * params	: la commande qui viens d'etre taper + la struct principal
 * return	: -1 si erreur, 0 si tout est ok
 * def		:	cree chainlst de char** de toutes les commande
 *				check toutes les erros possibles de chaques char **
 *
 */
