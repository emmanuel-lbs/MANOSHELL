
#include "../../includes/minishell.h"

static void	ft_get_pwd(t_struct *s, char *pwd)
{
	int		i;
	char	**mem;

	mem = ft_split((pwd), '/');
	i = 0;
	while (mem[i])
		i++;
	if (i == 1)
	{
		mem[0][0] = '/';
		mem[0][1] = '\0';
	}
	if (g_errna != 0)
		s->prompt = ft_strjoin("\033[0;31m➜ \033[1;36m", ft_strjoin(mem[i - 1], "\033[0m "));
	else
		s->prompt = ft_strjoin("\033[0;32m➜ \033[1;36m", ft_strjoin(mem[i - 1], "\033[0m "));
	i = 0;
	while (mem[i])
	{
		free(mem[i]);
		i++;
	}
	s->env = s->first->next;
	free(mem);
}

void	destroy_bob(t_struct *s)
{
	s->bob = s->first_bob;
	while (s->bob != NULL)
	{
		ft_free_double_char(s->bob->token);
		if (s->bob->fd_out)
			close(s->bob->fd_out);
		if (s->bob->fd_in)
			close(s->bob->fd_in);
		s->bob = s->bob->next;
	}
//	s->env = s->first;
//	while (s->env !- NULL)
//	{
//
//	}
	free(s->bob);
	free(s->first_bob);
}

int	main(int ac, char **av, char **envp)
{
	char		*str;
	t_struct	s;

//	s = malloc(&sizeof(&s));
	str = "";
	ft_check_path(&s, envp, ac, av);
	s.env = s.first;
	while (s.env->next)
	{
		printf(" %s\n", s.env->content);
		s.env = s.env->next;
	}
	printf(" %s\n", s.env->content);
	printf("cmp = %d\n", ft_strccmp("TERM=", "TERM", '='));
	//g_errna = errno;
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
		{
			printf ("\033[34;01mPERFECT\033[00m\n");
			s.data.id1 = malloc(sizeof(int) * s.no_pipe + 1);
			ft_exec(&s, str);
			s.env = s.first;
		}
		g_errna = errno;
		//	free(str);
		//destroy_bob(&s);
	}
}
