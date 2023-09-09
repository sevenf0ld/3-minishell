# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/09 18:31:26 by maiman-m          #+#    #+#              #
#    Updated: 2023/09/10 01:04:48 by maiman-m         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PROG_NAME = builtins

CC = cc

CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g3

# CPPFLAGS = -I include -I libft/include

CPPFLAGS = -I libft/include -I lex.h

LDFLAGS = -Llibft -lft -lreadline -L/usr/local/opt/readline/lib -I/usr/local/opt/readline/include

# SOURCE = echo.c pwd.c

# SRCS = $(addprefix src/, $(SOURCE))

SRCS = lex.c init.c

OBJS = $(SRCS:.c=.o)

all: $(OBJS)
	cd libft && $(MAKE)
	$(CC) $^ $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) -o $(PROG_NAME)

clean:
	cd libft && $(MAKE) clean
	rm -rf $(OBJS)
	rm -rf a.out*

fclean: clean
	cd libft && $(MAKE) fclean
	rm -rf $(PROG_NAME)

re: fclean all

.PHONY: all clean fclean re
