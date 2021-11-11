# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elabasqu <elabasqu@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/23 15:33:24 by elabasqu          #+#    #+#              #
#    Updated: 2021/10/24 16:44:45 by elabasqu         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

#----------------------------------------------#
#-------------------SOURCE---------------------#
#----------------------------------------------#

SRCS = ft_memset.c \
	   ft_bzero.c \
	   ft_memcpy.c \
	   ft_strlen.c \
	   ft_isdigit.c \
	   ft_isalnum.c \
	   ft_isascii.c \
	   ft_toupper.c \
	   ft_tolower.c \
	   ft_strchr.c \
	   ft_strrchr.c \
	   ft_isalpha.c \
	   ft_is_ispaces.c \
	   ft_isprint.c \
	   ft_memchr.c \
	   ft_memcmp.c \
	   ft_strlcat.c \
	   ft_strncmp.c \
	   ft_strlcpy.c \
	   ft_strnstr.c \
	   ft_atoi.c \
	   ft_strdup.c \
	   ft_calloc.c \
	   ft_strjoin.c \
	   ft_split.c \
	   ft_itoa.c \
	   ft_strmapi.c \
	   ft_putchar_fd.c \
	   ft_putstr_fd.c \
	   ft_putendl_fd.c \
	   ft_putnbr_fd.c \
	   ft_power.c \
	   ft_printf_error.c \
	   ft_free_double_char.c \
	   get_next_line.c \
	   get_next_line_utils.c 

NAME		= libft.a
LIB			= libft.h
OBJS		= $(SRCS:.c=.o)
CC			= clang
RM 			= rm -f
CFLAGS		= -Wall -Wextra -Werror
AR			= ar -rcs

all:		${NAME}

$(NAME):	${OBJS} ${LIB}
	${AR} ${NAME} ${OBJS}


%.o: %.c	${LIB} 
	${CC} ${CFLAGS} -c $< -o $@


clean:
	${RM} ${OBJS}

fclean:		clean
	${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re bonus 
