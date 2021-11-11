/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elabasqu <elabasqu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 13:35:33 by elabasqu          #+#    #+#             */
/*   Updated: 2021/06/05 19:25:37 by elabasqu         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*cut_for_rest(char *str)
{
	char				*rest;
	unsigned int		i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
	{
		free(str);
		return (NULL);
	}
	rest = ft_substr(str, i + 1, (ft_strlen(str) - i));
	free(str);
	return (rest);
}

char	*cut_for_line(char *str)
{
	int		i;
	char	*line;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	line = malloc(sizeof(char) * (i + 1));
	if (!(line))
		return (NULL);
	return (ft_gnl_cpy(line, str, i + 1));
}

int	ft_norme(int *i, char *more_line_then_rest, int fd, char *tmp)
{
	int	read_return;

	*i = ft_isline(more_line_then_rest, *i);
	read_return = read(fd, tmp, BUFFER_SIZE);
	if (read_return == -1)
	{
		free(tmp);
		return (-1);
	}
	return (read_return);
}

int	get_next_line(int fd, char **line)
{
	char			*tmp;
	static char		*more_line_then_rest;
	int				read_return;
	int				i;

	i = 0;
	read_return = 1;
	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	tmp = malloc(BUFFER_SIZE + 1);
	if (!(tmp))
		return (-1);
	while (ft_isline(more_line_then_rest, i) != -1 && read_return != 0)
	{
		read_return = ft_norme(&i, more_line_then_rest, fd, tmp);
		tmp[read_return] = '\0';
		more_line_then_rest = ft_gnl_join(more_line_then_rest, tmp);
	}
	free(tmp);
	*line = cut_for_line(more_line_then_rest);
	more_line_then_rest = cut_for_rest(more_line_then_rest);
	if (read_return == 0)
		return (0);
	return (1);
}
