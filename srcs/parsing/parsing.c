/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elabasqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 14:52:46 by elabasqu          #+#    #+#             */
/*   Updated: 2022/02/10 14:53:26 by elabasqu         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	number_pipe(char *str)
{
	int	i;
	int	pip;

	pip = 0;
	i = 0;
	while (str[i])
	{
		if (ft_is_quote(str[i]) == 1)
			skip_quote(str, str[i], &i);
		if (str[i] == '|')
			pip++;
		i++;
	}
	return (pip);
}

int	parsing(char *str, t_struct *s)
{
	char	**tokeniser;

	if (no_commande(str) == -1)
		return (-1);
	if (command_syntax(str) == -1)
		return (-1);
	tokeniser = split_shell(str, s);
	if (tokeniser == NULL)
		return (-1);
	s->bob = create_bob(tokeniser);
	s->first_bob = s->bob;
	s->no_pipe = number_pipe(str);
	ft_free_double_char(tokeniser);
	return (0);
}
