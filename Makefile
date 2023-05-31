# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: paolococci <paolococci@student.42.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/04 12:45:42 by lmasetti          #+#    #+#              #
#    Updated: 2023/05/30 11:54:39 by paolococci       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SRCS = main.c builtins.c builtins2.c builtins3.c check_builtins.c execute.c \
		ft_split.c handle_variables.c lst_utils.c lst_utils2.c \
		parse_input.c redirect.c new_process.c  \
		utils2.c utils.c utilscalloc.c utilsflags.c variables.c variables2.c utils_path.c path.c pipe.c

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

.PHONY: all clean fclean re .c.o
