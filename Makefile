# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pcocci <pcocci@student.42firenze.it>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/04 12:45:42 by lmasetti          #+#    #+#              #
#    Updated: 2023/06/23 10:10:19 by pcocci           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SRCS = main.c builtins.c builtins2.c builtins3.c check_builtins.c \
		ft_split.c handle_variables.c handle_variables1.c handle_variables2.c \
		parse_input.c parse_input2.c parse_input3.c pipe.c pipe1.c \
		pipe2.c pipe3.c redirect.c new_process.c utils_path.c here_doc.c \
		utils2.c utils.c utilscalloc.c utilsflags.c variables.c variables2.c \
		builtins4.c here_dochelp.c search_doc.c \

OBJS = $(SRCS:.c=.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror -g

%.o: %.c
	$(CC) -c $(CFLAGS) $?

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lreadline

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

valgrind:
	valgrind -s --leak-check=full --show-leak-kinds=all --suppressions=./readline.supp --track-origins=yes ./minishell

.PHONY: all clean fclean re .c.o
