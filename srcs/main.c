

#include "../includes/minishell.h"
#include "../includes/structure.h"

int		heredocs(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '<' && str[i + 1] == '<')
		{
			i++;
			if (str[i] == '<')
			{
//				fct_heredoc(str);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

static void	ft_get_pwd(t_struct *s, char *pwd)
{
	int		i;
	char	**mem;

	i = 0;
	mem = ft_split((pwd), '/');
	i = 0;
	while (mem[i])
		i++;
	s->prompt = ft_strjoin("\033[1;36m", ft_strjoin(mem[i - 1], " :\033[0m "));
	i = 0;
	while (mem[i])
	{
		free(mem[i]);
		i++;
	}
	free(mem);
}

int	main(int ac, char **av, char **envp)
{
	char		*str;
	int			i;
	t_struct	s;

	i = 0;
	str = "";
	/*while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}*/
	ft_check_path(&s, envp, ac, av);
	while (1)
	{
		//On stocke le stdin dans str,
		//on peut changer ça en le mettant dans une struct au besoin.
		ft_get_pwd(&s, s.pwd.content);
		str = readline(s.prompt);
		if (str == 0)
			break ;
		add_history(str);
		if (parsing(str, &s) == -1)
			printf ("\033[31;01mERROR\033[00m\n");
		else
			printf ("\033[34;01mPERFECT\033[00m\n");
		if (heredocs(str) == 0)
			ft_exec(&s, str);
	}
}
