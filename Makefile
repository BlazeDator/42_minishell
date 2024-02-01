# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pabernar <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/03 11:29:26 by pabernar          #+#    #+#              #
#    Updated: 2024/02/01 13:59:40 by pabernar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell 
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -O3
RM = rm -rf
LIBFT = libft/libft.a
LIBFT_DIR = libft/
SRCS = main.c minishell.c \
parser.c \
executer.c \
signal.c signal_handlers.c \
exit.c
SRCS_DIR = srcs/
OBJS = $(addprefix $(OBJS_DIR), $(SRCS:.c=.o))
OBJS_DIR = objs/
MINISH = -lreadline

all: $(NAME)

$(NAME): $(OBJS_DIR) $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(MINISH)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR):
	mkdir -p objs

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

norm:
	norminette -R CheckForbiddenSourceHeader headers/*.h srcs/*.c

leak: all
	valgrind --leak-check=full --show-leak-kinds=all \
		--suppressions=readline_leaks ./$(NAME)
