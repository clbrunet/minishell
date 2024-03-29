NAME=	minishell

SRCS=	srcs/main/main.c		\
		srcs/main/envp_utils.c	\
		srcs/main/signals.c		\
		srcs/ft/ft_strlen.c		\
		srcs/ft/ft_strcpy.c		\
		srcs/ft/ft_strncpy.c	\
		srcs/ft/ft_strcat.c		\
		srcs/ft/ft_strncat.c	\
		srcs/ft/ft_strncmp.c	\
		srcs/ft/ft_putstr_fd.c	\
		srcs/ft/ft_putchar_fd.c	\
		srcs/ft/ft_strchr.c		\
		srcs/ft/ft_strcmp.c		\
		srcs/ft/ft_lstsize.c	\
		srcs/ft/ft_strdup.c		\
		srcs/ft/ft_strndup.c	\
		srcs/ft/ft_isalpha.c	\
		srcs/ft/ft_isdigit.c	\
		srcs/ft/ft_isalnum.c	\
		srcs/ft/ft_size_nb.c	\
		srcs/ft/ft_atoi.c		\
		srcs/display/prompt.c	\
		srcs/parsing/get_next_line.c\
		srcs/parsing/utils.c		\
		srcs/parsing/free.c			\
		srcs/parsing/parse_line.c	\
		srcs/parsing/check_line.c	\
		srcs/parsing/parse_cmd.c	\
		srcs/parsing/parse_cmd_2.c	\
		srcs/parsing/parse_cmd_3.c	\
		srcs/parsing/parse_cmd_4.c	\
		srcs/parsing/parse_cmd_5.c	\
		srcs/parsing/parse_cmd_6.c	\
		srcs/parsing/parse_cmd_7.c	\
		srcs/parsing/parse_cmd_8.c	\
		srcs/parsing/parse_cmd_9.c	\
		srcs/parsing/parse_cmd_10.c \
		srcs/built_in/echo.c			\
		srcs/built_in/cd.c				\
		srcs/built_in/pwd.c				\
		srcs/built_in/export.c			\
		srcs/built_in/export_sort_env.c	\
		srcs/built_in/export_2.c		\
		srcs/built_in/export_3.c		\
		srcs/built_in/unset.c			\
		srcs/built_in/unset_2.c			\
		srcs/built_in/env.c				\
		srcs/built_in/exit.c			\
		srcs/execution/execute_cmds.c		\
		srcs/execution/execute_cmds2.c		\
		srcs/execution/execute_cmds_utils.c	\
		srcs/execution/redirect_stdin.c		\
		srcs/execution/dup_io.c				\
		srcs/execution/search_built_in.c	\
		srcs/execution/search_cmd_utils.c	\
		srcs/execution/search_cmd.c

OBJS=	$(SRCS:.c=.o)

CC=		clang
CFLAGS=	-Wall -Wextra -Werror -I./includes/

all:	$(NAME)

$(NAME):	$(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

bonus:	$(NAME)

clean:
	rm -f $(OBJS)

fclean:	clean
	rm -f $(NAME)

re:	fclean all

.PHONY:	all clean fclean re bonus
