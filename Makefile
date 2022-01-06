##############################  SOURCE & OBJETS  ###############################

SRCS = srcs/main.c \
		srcs/ft_check_path.c \
		srcs/parsing/parsing.c \
		srcs/parsing/ft_shell_split.c \
		srcs/parsing/tokenisation.c \
		srcs/parsing/syntax.c \
		srcs/parsing/utils.c \
		srcs/parsing/lst_bob.c \
		srcs/execute/ft_exec.c \
		srcs/execute/is_builtin.c \
		srcs/parsing/dollars.c \
		srcs/execute/builtin/ft_echo.c \
		srcs/execute/builtin/ft_pwd.c \
		srcs/execute/builtin/ft_cd.c \
		srcs/execute/builtin/ft_export.c \
		srcs/execute/builtin/ft_unset.c \
		srcs/execute/builtin/ft_env.c \
		

OBJS = $(SRCS:.c=.o)

################################  VARIABLES  ###################################

NAME = MANOSHELL

INCLUDE = includes/minishell.h includes/structure.h

RM = rm -f

GCCF = gcc -Wall -Wextra -fsanitize=address #-Werror 

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
