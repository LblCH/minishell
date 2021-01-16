# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ztawanna <ztawanna@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/02 23:10:05 by ztawanna          #+#    #+#              #
#    Updated: 2021/01/16 10:03:33 by cdrennan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell

CC = clang

CFLAGS = -Wall -Wextra -Werror

LIBFT = -L libft -lft

SRCS = minishell.c parcer.c ./gnl/get_next_line.c ./gnl/get_next_line_utils.c \
		utils.c lsts.c $(wildcard buildins/*.c) command_run.c env_utils.c cmd_exec_utils.c
#		$(addsuffix .c, $(addprefix srcs/srcs/, $(SRCS)))

OBJS = $(SRCS:.c=.o)

$(%.o): $(%.c)
	@printf "\033[0;33mCompiling minishell objects... %-33.33s\r" $@
	$(CC) -o $@ -c $^

all: $(NAME)

$(NAME): $(OBJS)
	@echo "\n"
	@make -C libft/
	@echo "\033[0;32mCompiling minishell..."
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT)
	@echo "\n\033[0mDone !"

clean:
	@echo "\033[0;31mCleaning libft..."
	@make clean -C libft/
	@echo "\nDeleting binaries..."
	@rm -f $(OBJS)
	@echo "\033[0m"

fclean:
	@echo "\033[0;31mCleaning libft..."
	@make fclean -C libft/
	@echo "\nDeleting objects..."
	@rm -f $(OBJS)
	@echo "\nDeleting executable..."
	@rm -f $(NAME)
	@echo "\033[0m"

re: fclean all
