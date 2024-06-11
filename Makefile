# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/10 18:09:38 by marvin            #+#    #+#              #
#    Updated: 2024/06/10 18:09:38 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC_DIR = ./src
OBJ_DIR = ./obj

CC = cc
FLAGS = -Wall -Wextra -Werror -g

HEADER = -I ./include

# ls -1 *.c | sed -z 's/\n/ \\\n\t\t\t/g'

SRC =	00_t_all.c \
		01_t_philo.c \
		02_t_philo_thread.c \
		check_format.c \
		main.c \
		parsing.c \
		size_ttab_utils.c
OBJ =	$(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

all: $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@test -d $(OBJ_DIR) || mkdir $(OBJ_DIR)
	@$(CC) $(FLAGS) -c $< -o $@ $(HEADER)

$(NAME): $(OBJ)
	@echo "\001\e[1;32m\002Compiling philo \001\e[0m\002"
	@$(CC) $(OBJ) $(HEADER) -o $(NAME)

run: all
	@clear
	@./$(NAME)

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -rf $(NAME)

re: clean all

.PHONY: all, run, clean, fclean, re