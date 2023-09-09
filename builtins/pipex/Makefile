# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maiman-m <maiman-m@student.42kl.edu.my>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/30 16:10:04 by maiman-m          #+#    #+#              #
#    Updated: 2023/06/07 16:25:38 by maiman-m         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PROG_NAME = pipex

CC = cc

CFLAGS = -Wall -Wextra -Werror

CPPFLAGS = -I include -I libft/include

LDFLAGS = -Llibft -lft

SOURCE = main.c processes.c utils.c

SRCS = $(addprefix src/, $(SOURCE))

OBJS = $(SRCS:.c=.o)

all: $(OBJS)
	cd libft && $(MAKE)
	$(CC) $^ $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) -o $(PROG_NAME)

clean:
	cd libft && $(MAKE) clean
	rm -rf $(OBJS)

fclean: clean
	cd libft && $(MAKE) fclean
	rm -rf $(PROG_NAME)

re: fclean all

.PHONY: all clean fclean re
