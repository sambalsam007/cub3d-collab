# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pdaskalo <pdaskalo@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/01 16:36:52 by pdaskalo          #+#    #+#              #
#    Updated: 2025/09/11 16:25:33 by pdaskalo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                                   COLORS                                     #
# **************************************************************************** #
RESET	= \033[0m
RED		= \033[1;31m
GREEN	= \033[1;32m
YELLOW	= \033[1;33m
BLUE	= \033[1;34m
PURPLE	= \033[1;35m

# **************************************************************************** #
#                                   PROJECT                                    #
# **************************************************************************** #
NAME	= cub3d
CC		= cc
CFLAGS	= -Wall -Wextra -Werror -Iinclude -Ilibft
# MLX		= -lmlx -lXext -lX11 -lm

# **************************************************************************** #
#                                   FILES                                      #
# **************************************************************************** #
SRCDIR		= srcs

SRCS_CL_ER	= \
		$(SRCDIR)/clean_and_error/err_msg.c

SRCS_INIT 	= \
		$(SRCDIR)/init/parse_map.c \
		$(SRCDIR)/init/init_cubed.c \
		$(SRCDIR)/init/read_file.c \
		$(SRCDIR)/init/utils.c

SRCS_PROGRAM = \
		$(SRCDIR)/program/draw.c \
		$(SRCDIR)/program/utils.c \
		$(SRCDIR)/program/keys.c \
		$(SRCDIR)/program/player.c

SRCS_MAIN 	= $(SRCDIR)/main.c

SRC			= $(SRCS_INIT) $(SRCS_MAIN) $(SRCS_CL_ER) $(SRCS_PROGRAM)
OBJ			= $(SRC:.c=.o)

LIBFTDIR	= libft
LIBFT		= $(LIBFTDIR)/libft.a

UNAME		= $(shell uname)

ifeq ($(UNAME), Darwin)  # macOS
MLXDIR		= mlxlib
MLX			= $(MLXDIR)/libmlx.a
MLXFLAGS	= -framework OpenGL -framework AppKit
endif

ifeq ($(UNAME), Linux)
MLXDIR		= mlxlib_linux
MLX			= $(MLXDIR)/libmlx.a
MLXFLAGS	= -lX11 -lXext -lm
endif

# **************************************************************************** #
#                                   RULES                                      #
# **************************************************************************** #

all: banner $(NAME)

banner:
	@echo "\033[1;34m"
	@echo "   $(RED) ██████╗$(PURPLE)██╗   ██╗$(BLUE)██████╗ $(GREEN)██████╗ $(YELLOW)██████╗ $(RESET)"
	@echo "   $(RED)██╔════╝$(PURPLE)██║   ██║$(BLUE)██╔══██╗$(GREEN)╚════██╗$(YELLOW)██╔══██╗$(RESET)"
	@echo "   $(RED)██║     $(PURPLE)██║   ██║$(BLUE)██████╔╝$(GREEN) █████╔╝$(YELLOW)██║  ██║$(RESET)"
	@echo "   $(RED)██║     $(PURPLE)██║   ██║$(BLUE)██╔══██╗$(GREEN) ╚═══██╗$(YELLOW)██║  ██║$(RESET)"
	@echo "   $(RED)╚██████╗$(PURPLE)╚██████╔╝$(BLUE)██████╔╝$(GREEN)██████╔╝$(YELLOW)██████╔╝$(RESET)"
	@echo "   $(RED) ╚═════╝$(PURPLE) ╚═════╝ $(BLUE)╚═════╝ $(GREEN)╚═════╝ $(YELLOW)╚═════╝ $(RESET)"
	@echo "\033[0m"

$(LIBFT):
	@$(MAKE) -C $(LIBFTDIR)

$(MLXDIR)/libmlx.a:
	@$(MAKE) -C $(MLXDIR)

$(NAME): $(OBJ) $(LIBFT) $(MLXDIR)/libmlx.a
	@echo "$(BLUE)[CUB3D] Compiling project...$(RESET)"
	@$(CC) $(CFLAGS) -I$(MLXDIR) $(OBJ) $(LIBFT) -L$(MLXDIR) -lmlx -framework OpenGL -framework AppKit -o $(NAME)
	@echo "$(GREEN)[CUB3D] Compiled successfully ✔$(RESET)"

%.o: %.c
	@$(CC) $(CFLAGS) -I$(MLXDIR) -c $< -o $@

clean: banner
	@rm -rf $(OBJ)
	@$(MAKE) -C $(LIBFTDIR) clean
	@$(MAKE) -C $(MLXDIR) clean
	@echo "$(YELLOW)[CUB3D] Objects removed ✘$(RESET)"

fclean: banner
	@rm -rf $(OBJ)
	@echo "$(YELLOW)[CUB3D] Objects removed ✘$(RESET)"
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFTDIR) fclean
	@$(MAKE) -C $(MLXDIR) fclean
	@echo "$(RED)[CUB3D] Executable removed ✘$(RESET)"

re: banner fclean all