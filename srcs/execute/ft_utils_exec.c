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
		return (0);
	return (-1);
}

int	ft_isalnum_(int c)
{
	if (ft_isalpha_(c) || ft_isdigit(c))
		return (0);
	return (-1);
}