
#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "structure.h"



/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~PARSSING~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

char		**shell_split(char *str);
int			parsing(char *str, t_struct *s);



/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~EXEC~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/







/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~UTILS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		**ft_split(char const *s, char c);
void		ft_check_path(t_data *data, char **envp);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#endif
