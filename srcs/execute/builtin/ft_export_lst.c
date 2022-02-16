/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_lst.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rozhou <rozhou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 13:29:52 by rozhou            #+#    #+#             */
/*   Updated: 2022/02/16 13:29:53 by rozhou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ft_lstcontent_swp(t_list *lst1, t_list *lst2)
{
	char	*str;

	str = lst2->content;
	lst2->content = lst1->content;
	lst1->content = str;
}

t_list	*ft_lstcopy(t_struct *s)
{
	t_list	*mem;

	s->env = s->first;
	mem = ft_lstnew(NULL);
	while (s->env->next != NULL)
	{
		ft_lstadd_back(&mem->next, ft_lstnew(s->env->content));
		s->env = s->env->next;
	}
	ft_lstadd_back(&mem->next, ft_lstnew(s->env->content));
	mem = mem->next;
	return (mem);
}

void	ft_lstc(t_list **lst)
{
	t_list	*current;
	t_list	*next;

	current = *lst;
	current = current->next;
	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}
	*lst = NULL;
}

static void	ft_lst_swapall(t_list *first, t_list *mem, t_list *sortlist)
{
	while (first->next != NULL)
	{
		mem = first;
		while (mem->next != NULL)
		{
			mem = mem->next;
			if (ft_strcmp(first->content, mem->content) > 0)
				ft_lstcontent_swp(first, mem);
		}
		first = first->next;
	}
	while (mem->next != NULL)
	{
		mem = mem->next;
		if (ft_strcmp(first->content, mem->content) > 0)
			ft_lstcontent_swp(first, mem);
	}
}

void	ft_lstsort_str(t_struct *s)
{
	t_list	*mem;
	t_list	*first;
	t_list	*sortlist;

	mem = ft_lstcopy(s);
	first = mem;
	sortlist = first;
	ft_lst_swapall(first, mem, sortlist);
	first = sortlist;
	ft_lstprint(first);
	first = sortlist;
	ft_lstc(&sortlist);
	g_errna = 0;
}
