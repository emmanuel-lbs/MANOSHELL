/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elabasqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 15:44:32 by elabasqu          #+#    #+#             */
/*   Updated: 2021/11/11 16:02:51 by elabasqu         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURE_H
# define STRUCTURE_H

#include "minishell"


typedef struct	p_lst {

	char	**token;
	int		in;
	int		out;
	t_lst	*next;
}				t_lst;

typedef struct	p_struc {
	t_lst	*lst;

}				t_struct;

#endif STRUCTURE_H
