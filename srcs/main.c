

#include "../includes/minishell.h"
#include "../includes/structure.h"


int	main(int ac, char **av, char **envp)
{
	char		*str;
	int			i;
	t_struct	s;

	i = 0;
	str = "";
	ft_check_path(&s, envp);
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
		if (str == NULL)
			break ;
		add_history(str);
		if (parsing(str, &s) == -1)
			printf ("\033[31;01mERROR\033[00m\n");
		else
			printf ("\033[34;01mPERFECT\033[00m\n");
	}
}
