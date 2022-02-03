#ifndef STRUCTURE_H
# define STRUCTURE_H
# include "minishell.h"

typedef struct s_data{
	int		ac;
	char	**av;
	int		end[2];
	int		fd[2];
	int		n;
	int		id1;
	char	**path;
	char	**args;
	char	**envp;
	char	**env_path;
}				t_data;

typedef struct s_bob {
	char			**token;
	int				fd_in;
	int				fd_out;
	int				mode_out;
	int				mode_in;
	struct s_bob	*next;
}				t_bob;

typedef struct p_struc {
	t_bob	*bob;
	t_bob	*first_bob;
	char	*heredocs;
	int		no_pipe;
	t_data	data;
	t_list	*env;
	t_list	*first;
	t_list	pwd;
	t_list	old_pwd;
	t_list	home;
	char	*prompt;
}				t_struct;

#endif
