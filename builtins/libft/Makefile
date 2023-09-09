# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maiman-m <maiman-m@student.42kl.edu.my>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/29 19:23:00 by maiman-m          #+#    #+#              #
#    Updated: 2023/09/10 00:11:16 by maiman-m         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = cc

vpath %.c src

CFLAGS = -Wall -Wextra -Werror

CPPFLAGS = -I include

SOURCE = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
	   ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c \
	   ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c \
	   ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c \
	   ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c \
	   ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c \
	   ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c ft_strcmp.c \
	   ft_atoll.c get_next_line.c get_next_line_utils.c \

SRCS = $(addprefix src/,$(SOURCE))

OBJS = $(SRCS:.c=.o)

$(NAME): $(OBJS)
	ar rcs $@ $^

all: $(NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
