#include "../../../includes/minishell.h"

void	ft_cd(t_struct *s)
{
	char	*pwd;

	pwd = NULL;
	if (!s->bob->token[1])
	{
		if (chdir(s->home->content + 5))
			printf("%s : No such file or directory\n", s->home->content);
		else
		{
			pwd = getcwd(pwd, 0);
			if (pwd)
			{
				s->old_pwd->content = s->pwd->content;
				s->pwd->content = pwd;
				s->pwd->content = ft_strjoin("PWD=", s->pwd->content);
				s->old_pwd->content = ft_strjoin("OLD", s->old_pwd->content);
			}
		}
	}
	else if (ft_strcmp(s->bob->token[1], "-") == 0)
	{
		if (chdir(s->old_pwd->content + 7))
			printf("%s : No such file or directory\n", s->old_pwd->content + 7);
		else
		{
			pwd = getcwd(pwd, 0);
			if (pwd)
			{
				s->old_pwd->content = s->pwd->content;
				s->pwd->content = pwd;
				s->pwd->content = ft_strjoin("PWD=", s->pwd->content);
				s->old_pwd->content = ft_strjoin("OLD", s->old_pwd->content);
			}
		}
	}
	else
	{
		printf("s->bob->token = %s\n", s->bob->token[1]);
		if (chdir(s->bob->token[1]))
			printf("%s : No such file or directory\n", s->bob->token[1]);
		else
		{
			pwd = getcwd(pwd, 0);
			if (pwd)
			{
				s->old_pwd->content = s->pwd->content;
				s->pwd->content = pwd;
				s->pwd->content = ft_strjoin("PWD=", s->pwd->content);
				s->old_pwd->content = ft_strjoin("OLD", s->old_pwd->content);
			}
		}
	}
}
