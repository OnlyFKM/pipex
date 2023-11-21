# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: frcastil <frcastil@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/13 16:52:27 by frcastil          #+#    #+#              #
#    Updated: 2023/11/21 11:57:26 by frcastil         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
NAME_BONUS = pipex_bonus

CFLAGS = -Wextra -Wall -Werror
LIBFT = ./libft

SRCS = src/main.c\
	src/utils.c\

SRCS_BONUS = src_bonus/main_bonus.c\
	src_bonus/utils_bonus.c\

CC = gcc

OBJS = ${SRCS:.c=.o}

OBJS_BONUS = ${SRCS_BONUS:.c=.o}

all: $(LIBFT)/libft.a $(NAME)

bonus: $(LIBFT)/libft.a $(NAME_BONUS)

$(NAME): $(OBJS)
	@$(CC) -g $(CFLAGS) $(LIBFT)/libft.a $(OBJS) -o $(NAME)

$(NAME_BONUS): $(OBJS_BONUS)
	@$(CC) -g $(CFLAGS) $(LIBFT)/libft.a $(OBJS_BONUS) -o $(NAME_BONUS)

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)\n"

$(LIBFT)/libft.a:
	@make -C $(LIBFT)

clean:
	@rm -rf $(OBJS) $(OBJS_BONUS)
	@make -C $(LIBFT) clean

fclean: clean
	@rm -rf $(NAME) $(NAME_BONUS)
	@make -C $(LIBFT) fclean

re: fclean all

.PHONY: all clean fclean re bonus