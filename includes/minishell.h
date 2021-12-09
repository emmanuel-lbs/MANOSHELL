
#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "structure.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>



/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~PARSING~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*main fct of parsing*/
int			parsing(char *str, t_struct *s);
/*syntax*/
int			no_commande(char *str);
int			skip_quote(const char *s, char quote, int *i);
int			command_syntax(char *str);
/*split*/
int			ft_countwords(const char *s);
char		**split_shell(char *cmd);
/*utils*/
int			ft_is_chevron(char c);
int			ft_is_quote(char c);
/*lst_bob*/
t_bob		*create_bob(char **str);
void		add_back_bob(t_bob **bob, t_bob *add);
void		new_block(t_struct *s, char **str);
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~EXEC~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

int			ft_exec(t_struct *s);





/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~UTILS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

int			ft_check_path(t_struct *s, char **envp, int ac, char **av);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#endif
