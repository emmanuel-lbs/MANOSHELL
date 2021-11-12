
#include "../includes/minishell.h"

void	ft_check_path(t_data *data, char **envp)
{
	int	i;

	i = 0;
	while (ft_strncmp(envp[i], "PATH=", 5))
		i++;

	data->env_path = ft_split((envp[i]), ':');
	data->env_path[0] = (data->env_path[0] + 5);
}
