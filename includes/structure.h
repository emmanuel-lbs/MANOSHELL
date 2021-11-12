#ifndef STRUCTURE_H
# define STRUCTURE_H
# include "minishell.h"

typedef struct s_data{
	char	**env_path;
}				t_data;

typedef struct p_lst {
	char			**token;
	int				in;
	int				out;
	struct t_lst	*next;
}				t_lst;

typedef struct p_struc {
	t_lst	*lst;
	t_data	data;
	t_list	env;
}				t_struct;

#endif
