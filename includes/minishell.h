
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
# include <errno.h>



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
<<<<<<< HEAD
int			ft_is_quote(char c);
=======
int			t_is_quote(char c);
>>>>>>> 4fcd040ce54581d2c6b0be16989c98bc8833baee
/*lst_bob*/
t_bob		*create_bob(char **str);
void		add_back_bob(t_bob **bob, t_bob *add);
<<<<<<< HEAD
void		new_block(t_struct *s, char **str);
=======
t_bob		*new_block(char *str);
/*split*/
char		**split_shell(char *cmd);
>>>>>>> 4fcd040ce54581d2c6b0be16989c98bc8833baee
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~EXEC~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*Builtin function*/
void		ft_echo(t_struct *s);
void		ft_cd(t_struct *s);
void		ft_pwd(void);
void		ft_export(t_struct *s);
void		ft_unset(t_struct *s);
void		ft_env(t_struct *s);
/*Main execution*/
int			is_builtin(t_struct *s);
int			ft_exec(t_struct *s, char *str);




/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~UTILS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

int			ft_check_path(t_struct *s, char **envp, int ac, char **av);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#endif
