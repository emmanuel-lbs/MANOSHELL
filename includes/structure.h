#ifndef STRUCTURE_H
# define STRUCTURE_H
# include "minishell.h"

typedef struct s_data{
	int		ac;
	char	**av;
	int		fd[2];
	int		end[2];
	int		n;
	int		id1;
	int		id2;
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
	struct s_bob	*next;
}				t_bob;

typedef struct p_struc {
	t_bob	bob;
	t_data	data;
	t_list	env;
}				t_struct;

#endif
