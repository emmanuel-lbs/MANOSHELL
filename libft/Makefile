# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rozhou <rozhou@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/23 15:33:24 by elabasqu          #+#    #+#              #
#    Updated: 2022/02/24 10:19:34 by elabasqu         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

#----------------------------------------------#
#-------------------SOURCE---------------------#
#----------------------------------------------#

SRCS = ft_memset.c \
	   ft_bzero.c \
	   ft_memcpy.c \
	   ft_len_jusque.c \
	   ft_strlen.c \
	   ft_is_all.c \
	   ft_is_all_2.c \
	   ft_toupper.c \
	   ft_add_char.c \
	   ft_tolower.c \
	   ft_strchr.c \
	   ft_strrchr.c \
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
	   get_next_line_utils.c \
	   ft_lstlast.c \
	   ft_lstadd_back.c \
	   ft_lstclear.c \
	   ft_lstnew.c \
	   ft_lstadd_front.c \
	   ft_lstdelone.c \
	   ft_strcmp.c \

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
