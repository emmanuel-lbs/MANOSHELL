#include "../../includes/minishell.h"

void	ft_redir_close(int fd, int std)
{
	dup2(fd, std);
	close(fd);
}