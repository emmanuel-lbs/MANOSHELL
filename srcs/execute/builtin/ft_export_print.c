/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_print.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rozhou <rozhou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 13:29:54 by rozhou            #+#    #+#             */
/*   Updated: 2022/02/24 10:06:28 by elabasqu         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	ft_checkequal(t_list *lst, int i, char **mem)
{
	if (ft_strchr(lst->content, '='))
	{
		mem = ft_splitone(lst->content, '=');
		printf("declare -x %s=\"", mem[0]);
		while (mem && mem[i])
		{
			printf("%s", mem[i]);
			i++;
		}
		i = 1;
		printf("\"\n");
		free(mem[0]);
		free(mem[1]);
		free(mem);
	}
	else
		printf("declare -x %s\n", lst->content);
}

void	ft_lstprint(t_list *lst)
{
	int		i;
	char	**mem;

	mem = NULL;
	i = 1;
	while (lst->next != NULL)
	{
		ft_checkequal(lst, i, mem);
		lst = lst->next;
	}
	ft_checkequal(lst, i, mem);
}
