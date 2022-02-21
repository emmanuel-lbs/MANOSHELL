#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <termios.h>
# include "../libft/libft.h"
# include "structure.h"

extern int			g_errna;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~PARSING~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*main fct of parsing*/
int			parsing(char *str, t_struct *s);
/*syntax*/
int			no_commande(char *str);
int			skip_quote(char *s, char quote, int *i);
int			command_syntax(char *str);
/*split*/
int			ft_countwords(char *s);
char		*one_token(char *cmd, int *i, t_struct *s);
char		*one_token_quote(char *cmd, int *i, t_struct *s);
char		**split_shell(char *cmd, t_struct *s);
/*quotes*/
int			verif_quote(char *cmd, int i);
int			dollar_in_quote(char *cpy, char *cmd, int *i, int *j, t_struct *s);
int			cpy_quote(char *cpy, char *cmd, int *i, int *j, t_struct *s);
int			verif_quote(char *cmd, int i);
/*DOLLARS*/
char		*change_dollars(char *dollars, char *var);
char		*dollar_not_interpret(char *cmd, int *i);
int			search_dollars(char *dollars, t_struct *s);
char		*one_token_dollars(char *cmd, int *i, t_struct *s);
char		*fusion_double_token(char *str, char *cmd, int *i, t_struct *s);
int			resize_len_for_dollar(char *cmd, int start, int end, t_struct *s);
/*FAKE_DOLLARS*/
int	not_a_dollar(char *cmd, int i);
char	*fake_dollars(char *cmd, int *i, t_struct *s);
/*DOLLARS_UTILS*/
char		*dollars_erno(char **a_token, int *i);
char		*normal_token(char *cmd, int *i, t_struct *s);
int			resize_len_for_dollar(char *cmd, int start, int end, t_struct *s);
int			strlen_var_env_no_space(char *var);
char		*change_dollars(char *dollars, char *var);
char		*change_dollars_no_space(char *dollars, char *var);
int			search_diff(char *cmd, int *start, t_struct *s);
int			diff_in_var_env(char *var);
int			strlen_var_env(char *var);
int			last_caractr(char *var);
int			len_env(char *env);
/*CHEVRONS*/
int			gere_chevron(char **str, int *actual_word, t_bob *bob);
int			lst_ajustement(char **str, int start, int end);
char		*cpy_chevron(char *cmd, int *i);
/*COUNT*/
void		how_many_token(char *s, int *i, int *nb);
int			ajustement(char *s, t_struct *struc);
int			wcount(char *s);
/*VAR_FIRST_TOKEN*/
int			is_cmd(t_struct *s, char *str);
int			ft_is_builtin(char *str);
int			is_first_word_and_dollars(char *cmd, int i);
char		*next_token(char *a_token);
int			is_first_word_and_dollars(char *cmd, int i);
char		*first_word_fct(char *a_token);
/*utils*/
int			ft_is_chevron(char c);
int			ft_is_quote(char c);
void		add_char(char *cpy, char *str, int *i, int *j);
int			should_mod(char *cmd, int i, char *a_token, t_struct *s);
void		modif_token(char *a_token, char **lst_tkn, int *nb_word);
int			token_len(char *cmd, int i);
/*lst_bob*/
t_bob		*create_bob(char **str);
void		add_back_bob(t_bob **bob, t_bob *add);
void		new_block(t_struct *s, char **str);
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~EXEC~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*Utils*/
int			ft_isalnum_(int c);
int			ft_isalpha_(int c);
void		ft_delfirst(t_list **lst);
void		ft_delone(t_list **lst);
int			ft_strclen(char *str, char c);
void		ft_setenv_null(t_struct *s);
int			ft_pathfinder(t_struct *s, int n);
void		ft_redirect(t_bob *bob);
void		ft_redir_close(int fd, int std);
void		ft_setenv_null(t_struct *s);
int			ft_strgetchar(char *str, char c);
int			ft_strccmp(const char *s1, const char *s2, char c, int i);
void		ft_lstcontent_swp(t_list *lst1, t_list *lst2);
t_list		*ft_lstcopy(t_struct *s);
void		ft_lstc(t_list **lst);
void		ft_lstsort_str(t_struct *s);
char		*ft_strjoinfree(const char *s1, const char *s2, int alloc_args);
/*Builtin function*/
void		ft_echo(t_struct *s);
void		ft_cd(t_struct *s);
void		ft_pwd(void);
int			ft_checkdup(t_struct *s, char *str);
void		ft_lstprint(t_list *lst);
void		ft_export(t_struct *s);
void		ft_unset(t_struct *s);
void		ft_env(t_struct *s);
void		ft_exit(t_struct *s);
void		ft_pipexit(t_struct *s);
/*Main execution*/
int			is_builtin(t_struct *s);
int			is_first_builtin(t_struct *s, int i);
void		ft_fork_exec(t_struct *s, int *fd_in, int i);
int			ft_exec(t_struct *s, int i, int status, int builtin);
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~SIGNALS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void		ctrl_c(int n);
void		ctrl_child(int n);
void		ctrl_quit(int n);
void		ft_signal(t_struct *s);
void		sig_airdog(int n);
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~OTHER~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void		beging_hered(char	**str, int actual_word, t_bob *bob);
t_bob		*heredocs_bob(t_bob *bob);
char		*heredocs_end_word(char	**token, int i);
int			is_heredocs(t_struct *s);
int			ft_check_path(t_struct *s, char **envp, int ac, char **av);

void	printf_lst(t_bob *bob);////////////////
#endif
