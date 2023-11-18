# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: frcastil <frcastil@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/13 16:52:27 by frcastil          #+#    #+#              #
#    Updated: 2023/11/18 17:26:21 by frcastil         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CFLAGS = -Wextra -Wall -Werror -g3
LIBFT = ./libft

SRCS = src/main.c\
	src/utils.c\

CC = gcc

OBJS = ${SRCS:.c=.o}

all: $(LIBFT)/libft.a $(NAME)

$(NAME): $(OBJS)
	@$(CC) -g $(CFLAGS) $(LIBFT)/libft.a $(OBJS) -o $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)\n"

$(LIBFT)/libft.a:
	@make -C $(LIBFT)

clean:
	@rm -rf $(OBJS)
	@make -C $(LIBFT) clean

fclean: clean
	@rm -rf $(NAME)
	@make -C $(LIBFT) fclean

re: fclean all

.PHONY: all clean fclean re