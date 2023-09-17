# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/15 12:21:40 by maiman-m          #+#    #+#              #
#    Updated: 2023/09/17 14:28:20 by maiman-m         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PROG_NAME = v1

CC = cc

CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g3

# CPPFLAGS = -I include -I libft/include

CPPFLAGS = -I libft/include -I mini.h

# LDFLAGS = -Llibft -lft -lreadline -L/usr/local/opt/readline/lib -I/usr/local/opt/readline/include

LDFLAGS = -Llibft -lft -lreadline -I/usr/local/opt/readline/include

# SOURCE =

# SRCS = $(addprefix src/, $(SOURCE))

SRCS = main.c tokenizer.c init_token.c d_ll_convert.c \
	   lexer.c lexer_utils.c \
	   parser.c parser_utils.c init_cmd.c

OBJS = $(SRCS:.c=.o)

all: $(PROG_NAME)

$(PROG_NAME): $(OBJS)
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
