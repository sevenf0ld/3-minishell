# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/09 18:31:26 by maiman-m          #+#    #+#              #
#    Updated: 2023/09/11 16:18:42 by maiman-m         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PROG_NAME = builtins

CC = cc

CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g3

# CPPFLAGS = -I include -I libft/include

CPPFLAGS = -I libft/include -I build.h

# LDFLAGS = -Llibft -lft -lreadline -L/usr/local/opt/readline/lib -I/usr/local/opt/readline/include

LDFLAGS = -Llibft -lft -lreadline -I/usr/local/opt/readline/include

# SOURCE = 

# SRCS = $(addprefix src/, $(SOURCE))

SRCS = lex.c init_token.c parse.c init_cmd.c set.c init_split.c

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
