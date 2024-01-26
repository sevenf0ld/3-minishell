# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: folim <folim@student.42kl.edu.my>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/15 12:21:40 by maiman-m          #+#    #+#              #
#    Updated: 2024/01/26 12:02:26 by maiman-m         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PROG_NAME = v1

CC = clang

# CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g3

CFLAGS = -Wall -Wextra -Werror -g3

# CPPFLAGS = -I include -I libft/include

CPPFLAGS = -I/libft/include -I/mini.h

# LDFLAGS = -Llibft -lft -lreadline -L/usr/local/opt/readline/lib -I/usr/local/opt/readline/include

LDFLAGS = -Llibft -lft -lreadline -L/goinfre/folim/.brew/opt/readline/lib -I/goinfre/folim/.brew/opt/readline/include #for rl_replace_line

# LDFLAGS = -Llibft -lft -lreadline -I/usr/local/opt/readline/include

# LDFLAGS = -Llibft -lft -lreadline

# SOURCE =

# SRCS = $(addprefix src/, $(SOURCE))

SRCS = main.c init_mini.c tokenizer.c tokenizer_utils.c init_token.c d_ll_convert.c \
	   lexer.c split.c split_utils.c split_utils2.c reject.c reject_utils.c reject_utils2.c expand.c expand_utils4.c expand_utils5.c replace.c lexer_utils.c \
	   parser.c init_cmd.c init_cmd_utils.c init_cmd_utils2.c init_pipe.c parser_utils.c parser_utils2.c parser_utils3.c parser_utils4.c \
           heredoc.c \
           n_builtins.c concurrent.c \
           signal.c \
	   b_echo.c b_dir.c b_environ.c b_exit.c \
	   init_env.c init_fixed.c fixed_utils.c \
	   err_handling.c free.c
	   

OBJS = $(SRCS:.c=.o)

#all: $(PROG_NAME)

$(PROG_NAME): $(OBJS)
	cd libft && $(MAKE)
	$(CC) $^ $(CPPFLAGS) $(LDFLAGS) -o $(PROG_NAME)

clean:
	cd libft && $(MAKE) clean
	rm -rf $(OBJS)
	rm -rf a.out*

fclean: clean
	cd libft && $(MAKE) fclean
	rm -rf $(PROG_NAME)

re: fclean all $(PROG_NAME)

.PHONY: all clean fclean re
