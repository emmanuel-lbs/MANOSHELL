

#include "../includes/minishell.h"
#include "../includes/structure.h"


int	main(int ac, char **av, char **envp)
{
	char		*str;
	int			i;
	t_struct	s;

	i = 0;
	str = "";
	ft_check_path(&s.data, envp);
	while (s.data.env_path[i])
	{
		printf("data = %s\n", s.data.env_path[i]);
		i++;
	}
	while (1)
	{
		//On stocke le stdin dans str,
		//on peut changer ça en le mettant dans une struct au besoin.
		str = readline("MANULL le sang$ ");
		printf("%s\n",str);
		if (str == NULL)
			break;
		if (parsing)
		{
			exec
		}
		dprintf(1, "%d\n", ft_countwords(str));;
	}
}
