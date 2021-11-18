

#include "../../includes/minishell.h"

t_bob	*lastbob(t_bob *bob)
{
	if (!bob)
		return (0);
	while (bob->next)
		bob = bob->next;
	return (bob);
}

void	add_back_bob(t_bob **bob, t_bob *add)
{

	if (*bob == NULL)
	{
		*bob = add;
		return ;
	}
	lastbob(*bob)->next = add;
}

t_bob	*new_block(char *str)
{
	t_bob *bob;

	bob = malloc (sizeof(t_bob *));
	bob->token = malloc(sizeof(char *) * (ft_countwords(str) + 1));
	return (bob);
}

