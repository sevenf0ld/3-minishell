# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: folim <folim@student.42kl.edu.my>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/15 12:21:40 by maiman-m          #+#    #+#              #
#    Updated: 2024/02/05 12:56:22 by maiman-m         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PROG_NAME = minishell

CC = cc

CFLAGS = -Wall -Wextra -Werror -g3

CPPFLAGS = -I/libft/include -I/mini.h

LDFLAGS = -Llibft 

LDLIBS = -lft -lreadline

SRCS = main.c init_mini.c mini_utils.c mini_utils2.c tokenizer.c tokenizer_utils.c init_token.c d_ll_convert.c \
	   lexer.c split.c split_utils.c split_utils2.c reject.c reject_utils.c reject_utils2.c expand.c expand_utils.c expand_utils2.c expand_utils3.c expand_utils4.c expand_utils5.c replace.c lexer_utils.c delete.c \
	   parser.c init_cmd.c init_cmd_utils.c init_cmd_utils2.c init_pipe.c parser_utils.c parser_utils2.c parser_utils3.c parser_utils4.c parser_utils5.c parser_utils6.c \
           heredoc.c \
           n_builtins.c n_builtins_utils.c n_builtins_utils2.c concurrent.c \
           signal_parent.c signal_child.c \
	   b_echo.c b_dir.c b_unset_env.c b_export.c b_exit.c b_exit_utils.c \
	   init_env.c init_fixed.c fixed_utils.c \
	   err_handling.c err_handling_utils.c err_handling_utils2.c free.c free2.c
	   
OBJS = $(SRCS:.c=.o)

all: $(PROG_NAME)

$(PROG_NAME): $(OBJS)
	cd libft && $(MAKE)
	$(CC) $^ $(CPPFLAGS) $(LDFLAGS) $(LDLIBS) -o $(PROG_NAME)

clean:
	cd libft && $(MAKE) clean
	rm -rf $(OBJS)
	rm -rf a.out*

fclean: clean
	cd libft && $(MAKE) fclean
	rm -rf $(PROG_NAME)

re: fclean all

.PHONY: all clean fclean re
