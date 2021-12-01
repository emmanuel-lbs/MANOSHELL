

#include "../includes/minishell.h"
#include "../includes/structure.h"

//
//static void	ft_get_pwd(t_struct *s, char *pwd)
//{
//	int		i;
//	char	**mem;
//
//	i = 0;
//	mem = ft_split((pwd), '/');
//	i = 0;
//	while (mem[i])
//		i++;
//	s->prompt = ft_strjoin("\033[1;36m", ft_strjoin(mem[i - 1], " :\033[0m "));
//	i = 0;
//	while (mem[i])
//	{
//		free(mem[i]);
//		i++;
//	}
//	free(mem);
//}
//
int	main(int ac, char **av, char **envp)
{
	char		*str;
	t_struct	s;

	str = "";
//	ft_check_path(&s, envp, ac, av);
	while (1)
	{
		//On stocke le stdin dans str,
		//on peut changer ça en le mettant dans une struct au besoin.
//		ft_get_pwd(&s, s.pwd.content);
		str = readline("MANUUUL :  ");
		if (str == 0)
			break ;
		add_history(str);
		if (parsing(str, &s) == -1)
			printf ("\033[31;01mERROR\033[00m\n");
		else
		{
				printf ("\033[34;01mPERFECT\033[00m\n");
//				ft_exec(&s);
		}
//		if (heredocs(str) == 0)
	}
}
