
#include "../../includes/minishell.h"

int	g_errna = 0;

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

void ctrl_c(int n)
{
	(void)n;
	g_errna = 130;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ft_signal(t_struct *s)
{
	tcgetattr(0, &s->old_termios);
	tcgetattr(0, &s->new_termios);
    s->new_termios.c_lflag &= ~ECHOCTL;
	s->new_termios.c_cc[VQUIT] = 0;
    tcsetattr(0, TCSANOW, &s->new_termios);
	signal(SIGINT, ctrl_c);
}

int	main(int ac, char **av, char **envp)
{
	char			*str;
	t_struct		s;
	//struct termios termios;

//	s = malloc(&sizeof(&s));
	str = "";
	ft_check_path(&s, envp, ac, av);
	if (!isatty(0) || !isatty(1))
		return (1);
	/*s.env = s.first;
	while (s.env->next)
	{
		printf(" %s\n", s.env->content);
		s.env = s.env->next;
	}
	printf(" %s\n", s.env->content);
	printf("cmp = %d\n", ft_strccmp("TERM=", "TERM", '='));*/
	//g_errna = errno;
	while (1)
	{
		//On stocke le stdin dans str,
		//on peut changer ça en le mettant dans une struct au besoin.
		ft_get_pwd(&s, s.pwd.content);
		ft_signal(&s);
		str = readline(s.prompt);
		if (str == 0)
		{
			tcsetattr(0, TCSANOW, &s.old_termios);
			printf("exit\n");
			rl_on_new_line();
			rl_replace_line("", 0);
			g_errna = 0;
			break ;
		}
		add_history(str);
		if (parsing(str, &s) == -1)
		{
			g_errna = 0;
			printf ("\033[31;01mERROR\033[00m\n");
		}
		else
		{
			printf ("\033[34;01mPERFECT\033[00m\n");
			s.data.id1 = malloc(sizeof(int) * s.no_pipe + 1);
			ft_exec(&s, str);
			s.env = s.first;
		}
		//	free(str);
		//destroy_bob(&s);
	}
}
