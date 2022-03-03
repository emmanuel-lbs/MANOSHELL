/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rozhou <rozhou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 13:30:04 by rozhou            #+#    #+#             */
/*   Updated: 2022/03/03 12:14:11 by rozhou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_redir_close(int fd, int std)
{
	dup2(fd, std);
	close(fd);
}

void	ft_delone(t_list **lst)
{
	t_list	*tmp;
	t_list	*mem;

	tmp = *lst;
	mem = tmp->next;
	tmp->next = tmp->next->next;
	if (mem->tofree == 1)
		free(mem->content);
	free(mem);
}

void	ft_delfirst(t_list **lst)
{
	t_list	*tmp;
	t_list	*mem;

	tmp = *lst;
	mem = tmp;
	tmp = tmp->next;
	free(mem);
}

int	ft_isalpha_(int c)
{
	if ((64 <= c && c <= 90) || (97 <= c && c <= 122) || c == '_')
		return (1);
	return (0);
}

int	ft_isalnum_(int c)
{
	if (ft_isalpha_(c) || ft_isdigit(c))
		return (1);
	return (0);
}
