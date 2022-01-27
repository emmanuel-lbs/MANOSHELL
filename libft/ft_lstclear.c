/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rozhou <rozhou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 15:11:03 by rozhou            #+#    #+#             */
/*   Updated: 2022/01/27 12:37:03 by rozhou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*lst2;

	while (*lst)
	{
		lst2 = *lst;
		*lst = lst2->next;
		ft_lstdelone(lst2, del);
	}
	*lst = NULL;
}
