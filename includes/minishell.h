
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
# include <sys/types.h>
# include <sys/stat.h>

extern int         g_errna;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~PARSING~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*main fct of parsing*/
int			parsing(char *str, t_struct *s);
/*syntax*/
int			no_commande(char *str);
int			skip_quote(char *s, char quote, int *i);
int			command_syntax(char *str);
/*split*/
int			ft_countwords(char *s);
char		**split_shell(char *cmd, t_struct *s);
/*quotes*/
int			dollar_in_quote(char *cpy, char *cmd, int *i, int *j, t_struct *s);
int			cpy_quote(char *cpy, char *cmd, int *i, int *j, t_struct *s);
int			verif_quote(char *cmd, int i);
char		*one_token_quote(char *cmd, int *i, t_struct *s);
/*DOLLARS*/
char		*change_dollars(char *dollars, char *var);
char		*dollar_not_interpret(char *cmd, int *i);
int			search_dollars(char *dollars, t_struct *s);
char		*one_token_dollars(char *cmd, int *i, t_struct *s);
char		*fusion_double_token(char *str, char *cmd, int *i, t_struct *s);
int			resize_len_for_dollar(char *cmd, int start, int end, t_struct *s);
/*utils*/
int			ft_is_chevron(char c);
int			ft_is_quote(char c);
void		add_char(char *cpy, char *str, int *i, int *j);
int			should_i_modif_token(char *cmd, int i, char *a_token, t_struct *s);
void		modif_token(char *a_token, char **lst_tkn, int *nb_word);
/*lst_bob*/
t_bob		*create_bob(char **str);
void		add_back_bob(t_bob **bob, t_bob *add);
void		new_block(t_struct *s, char **str);
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~EXEC~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*Utils*/
int	        ft_isalnum_(int c);
int	        ft_isalpha_(int c);
/*Builtin function*/
int	        ft_strccmp(const char *s1, const char *s2, char c);
void		ft_echo(t_struct *s);
void		ft_cd(t_struct *s);
void		ft_pwd(void);
void		ft_export(t_struct *s);
void		ft_unset(t_struct *s);
void		ft_env(t_struct *s);
void	    ft_exit(t_struct *s);
void	    ft_pipexit(t_struct *s);
/*Main execution*/
int			is_builtin(t_struct *s);
int			ft_exec(t_struct *s, char *str);
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~OTHER~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void		beging_hered(char	**str, int actual_word, t_bob *bob);
void		heredocs(t_bob *bob, char	*end_word);
t_bob		*heredocs_bob(t_bob *bob);
char		*heredocs_end_word(char	**token, int i);
int			is_heredocs(t_struct *s);
int			ft_check_path(t_struct *s, char **envp, int ac, char **av);

#endif
