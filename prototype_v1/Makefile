# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/15 12:21:40 by maiman-m          #+#    #+#              #
#    Updated: 2023/10/28 12:30:37 by maiman-m         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PROG_NAME = v1

CC = cc

CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g3

# CFLAGS = -Wall -Wextra -Werror -g3

# CPPFLAGS = -I include -I libft/include

CPPFLAGS = -I libft/include -I mini.h

# LDFLAGS = -Llibft -lft -lreadline -L/usr/local/opt/readline/lib -I/usr/local/opt/readline/include

LDFLAGS = -Llibft -lft -lreadline -I/usr/local/opt/readline/include

# SOURCE =

# SRCS = $(addprefix src/, $(SOURCE))

SRCS = main.c tokenizer.c tokenizer_utils.c init_token.c d_ll_convert.c \
	   lexer.c lexer_utils.c lexer_utils2.c lexer_utils3.c \
	   parser.c init_cmd.c \
	   parser_utils.c parser_utils2.c

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
