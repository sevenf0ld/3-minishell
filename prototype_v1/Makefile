# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: folim <folim@student.42kl.edu.my>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/15 12:21:40 by maiman-m          #+#    #+#              #
#    Updated: 2023/11/21 03:12:51 by maiman-m         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# PROG_NAME = v1

# CC = cc

# CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g3

# # CFLAGS = -Wall -Wextra -Werror -g3

# # CPPFLAGS = -I include -I libft/include

# CPPFLAGS = -I libft/include -I mini.h

# # LDFLAGS = -Llibft -lft -lreadline -L/goinfre/folim/.brew/opt/readline/lib -I/goinfre/folim/.brew/opt/readline/include #for rl_replace_line
# # LDFLAGS = -Llibft -lft -lreadline -I/usr/local/opt/readline/include
# # LDFLAGS = -Llibft -lft -lreadline

# LDFLAGS = -Llibft -lft -lreadline -I/usr/local/opt/readline/include -L/usr/local/opt/readline/lib

# # SRCS = $(addprefix src/, $(SOURCE))

# SRCS = main.c tokenizer.c tokenizer_utils.c init_token.c d_ll_convert.c \
# 	   lexer.c lexer_utils.c lexer_utils2.c lexer_utils3.c lexer_utils4.c \
# 	   parser.c init_cmd.c \
# 	   parser_utils.c parser_utils2.c parser_utils3.c init_pipe.c \
# 	   err_handling.c n_builtins.c free.c signal.c
	   

# OBJS = $(SRCS:.c=.o)

# all: $(PROG_NAME)

# $(PROG_NAME): $(OBJS)
# 	cd libft && $(MAKE)
# 	$(CC) $^ $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) -o $(PROG_NAME)

# clean:
# 	cd libft && $(MAKE) clean
# 	rm -rf $(OBJS)
# 	rm -rf a.out*

# fclean: clean
# 	cd libft && $(MAKE) fclean
# 	rm -rf $(PROG_NAME)

# re: fclean all

# .PHONY: all clean fclean re


NAME		:= minishell

LIBFT		:= libft.a
LIBFT_PATH	:= "libft"

CC			:= cc

CFLAGS		:= -Wall -Werror -Wextra

SRCS := main.c tokenizer.c tokenizer_utils.c init_token.c d_ll_convert.c \
	   lexer.c lexer_utils.c lexer_utils2.c lexer_utils3.c lexer_utils4.c \
	   parser.c init_cmd.c \
	   parser_utils.c parser_utils2.c parser_utils3.c init_pipe.c \
	   err_handling.c n_builtins.c free.c signal.c

OBJS :=	$(SRCS:.c=.o)

# READLINE_PATH:=	/goinfre/homebrew/opt/readline
READLINE_PATH:=	/usr/local/opt/readline

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -Iinclude -I$(READLINE_PATH)/include

all: $(NAME)

$(LIBFT):
	@make -C $(LIBFT_PATH)

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) -o $(NAME) $(OBJS) -L$(LIBFT_PATH) -lft -L$(READLINE_PATH)/lib -lreadline

clean:
	@make clean -C $(LIBFT_PATH)
	@rm -f $(OBJS)

fclean: clean
	@make fclean -C $(LIBFT_PATH)
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
