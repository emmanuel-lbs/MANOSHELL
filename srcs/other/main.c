#include "../../includes/minishell.h"

int	g_errna = 0;

void	destroy_bob(t_struct *s)
{
	s->bob = s->first_bob;
	while (s->bob != NULL)
	{
		ft_free_double_char(s->bob->token);
		if (s->bob->fd_out != 1)
			close(s->bob->fd_out);
		if (s->bob->fd_in != 0)
			close(s->bob->fd_in);
		s->bob = s->bob->next;
	}
	free(s->data.id1);
	free(s->first_bob);
}

void	str_zero(void)
{
	printf("exit\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	g_errna = 0;
}

int	main(int ac, char **av, char **envp)
{
	char			*str;
	t_struct		s;

	ft_check_path(&s, envp, ac, av);
	if (!isatty(0) || !isatty(1))
		return (1);
	while (1)
	{
		ft_get_pwd(&s, s.pwd.content);
		ft_signal(&s);
		str = readline(s.prompt);
		tcsetattr(0, TCSANOW, &s.old_termios);
		if (str == 0)
		{
			str_zero();
			break ;
		}
		add_history(str);
		if (parsing(str, &s) == -1)
			g_errna = 0;
		else
		{
//			ft_exec(&s, 0, 0, 0);
			destroy_bob(&s);
		}
		free(str);
		free(s.prompt);
	}
}
/*
 * int	main(int ac, char **av, char **envp)
{
	char			*str;
	t_struct		s;

	ft_check_path(&s, envp, ac, av);
	if (!isatty(0) || !isatty(1))
		return (1);
	while (1)
	{
		ft_get_pwd(&s, s.pwd.content);
		ft_signal(&s);
		str = readline(s.prompt);
		tcsetattr(0, TCSANOW, &s.old_termios);
		if (str == 0)
		{
			str_zero();
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
			printf("gerrna = %d\n", g_errna);
			printf ("\033[34;01mPERFECT\033[00m\n");
			ft_exec(&s, 0, 0, 0);
			s.env = s.first;
			destroy_bob(&s);
		}
		free(str);
		free(s.prompt);
	}
}
*/
