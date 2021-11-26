#include "../../../includes/minishell.h"

void	ft_pwd(void)
{
	char	*str;

	str = NULL;
	str = getcwd(str, 0);
	if (str)
		printf("%s\n", str);
	free(str);
}
