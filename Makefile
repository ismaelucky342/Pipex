# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/08 21:48:13 by ismherna          #+#    #+#              #
#    Updated: 2024/10/08 22:31:54 by ismherna         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


G = \033[1;32m
Y = \033[1;33m
R = \033[0;31m
NC = \033[0m
RESET = \033[0m

NAME = pipex

SRC = exec.c \
      main.c \
      fork.c  # Añade otros archivos fuente aquí según sea necesario

OBJ_DIR = objects
OBJ = $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC))

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3

LIBFT = ./Libft/libft.a

all: $(NAME)
	@echo " 												"		
	@echo "$(G)██╗  ██╗██████╗     ██████╗ ██╗██████╗ ███████╗██╗  ██╗$(RESET)"
	@echo "$(G)██║  ██║╚════██╗    ██╔══██╗██║██╔══██╗██╔════╝╚██╗██╔╝$(RESET)"
	@echo "$(G)███████║ █████╔╝    ██████╔╝██║██████╔╝█████╗   ╚███╔╝ $(RESET)"
	@echo "$(G)╚════██║██╔═══╝     ██╔═══╝ ██║██╔═══╝ ██╔══╝   ██╔██╗ $(RESET)"
	@echo "$(G)     ██║███████╗    ██║     ██║██║     ███████╗██╔╝ ██╗$(RESET)"
	@echo "$(G)     ╚═╝╚══════╝    ╚═╝     ╚═╝╚═╝     ╚══════╝╚═╝  ╚═╝$(RESET)"
	@echo "$(G)  ismherna@student.42.fr - 42 Madrid - Ismael Hernández$(RESET)"

$(NAME): $(LIBFT) $(OBJ_DIR) $(OBJ)
	@echo "$(Y)--------------------------------------- Compiling Pipex ---------------------------------------$(NC)"
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)
	@echo "$(G)----------------------------------- Pipex Finished Compiling -----------------------------------$(NC)"

$(LIBFT):
	@echo "$(Y)------------------------------------ Compiling Libft ------------------------------------$(NC)"
	@make -sC ./Libft

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c -o $@ $<

clean:
	@make -sC ./Libft clean
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.DEFAULT_GOAL: all
.PHONY: all clean fclean re
