##############################  SOURCE & OBJETS  ###############################

SRCS = srcs/main.c \
		srcs/ft_check_path.c \
		srcs/parsing/parsing.c \
		srcs/parsing/ft_shell_split.c \
		srcs/parsing/syntax.c \
		srcs/execute/ft_exec.c \
		

OBJS = $(SRCS:.c=.o)

################################  VARIABLES  ###################################

NAME = MANOSHELL

INCLUDE = includes/minishell.h includes/structure.h

RM = rm -f

GCCF = gcc -Wall -Wextra #-Werror

##################################  RULES  #####################################

all :	libf $(NAME)


$(NAME):	$(INCLUDE) $(OBJS)
	$(GCCF) $(OBJS) -lreadline libft.a -o $(NAME)

%.o: %.c	$(INCLUDE) 
	${GCCF} -c $< -o $@ 

libf:
	$(MAKE) -C libft
	ln -sf libft/libft.a

############################  CLEAN & RE & phony  ##############################

clean:
	${MAKE}  -C libft/ fclean
	$(RM) libft.a
	${RM} ${OBJS} 

fclean:		clean
	$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re bonus libf


#################################### FIN  ######################################
