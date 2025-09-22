# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pdaskalo <pdaskalo@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/01 16:36:52 by pdaskalo          #+#    #+#              #
#    Updated: 2025/09/04 16:25:52 by pdaskalo         ###   ########.fr        #
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

SRCS_MAIN 	= $(SRCDIR)/main.c

SRC			= $(SRCS_INIT) $(SRCS_MAIN) $(SRCS_CL_ER)
OBJ			= $(SRC:.c=.o)

LIBFTDIR	= libft
LIBFT		= $(LIBFTDIR)/libft.a

# **************************************************************************** #
#                                   RULES                                      #
# **************************************************************************** #
SPINPID := .spinner.pid

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

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX) -o $(NAME)
	@$(MAKE)
	@echo "$(GREEN)[CUB3D] Compiled successfully ✔$(RESET)"

# $(NAME): $(OBJ) $(LIBFT)
# 	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX) -o $(NAME)
# 	@$(MAKE) --no-print-directory stop_spinner
# 	@echo "$(GREEN)[CUB3D] Compiled successfully ✔$(RESET)"

# Start the spinner once before building objects
# $(OBJ): | start_spinner

# start_spinner:
# 	@{ \
# 	  trap "exit" INT TERM; \
# 	  trap "kill 0" EXIT; \
# 	  i=0; \
# 	  while :; do \
# 	    case $$i in \
# 	      0) dots='.' ;; \
# 	      1) dots='..' ;; \
# 	      2) dots='...' ;; \
# 	    esac; \
# 	    printf "\r\033[K$(BLUE)[CUB3D] Compiling files%s$(RESET)" "$$dots"; \
# 	    sleep 0.2; \
# 	    i=$$(((i+1)%3)); \
# 	  done \
# 	} & echo $$! > $(SPINPID)

# stop_spinner:
# 	@{ \
# 	  if [ -f $(SPINPID) ]; then \
# 	    kill $$(cat $(SPINPID)) >/dev/null 2>&1 || true; \
# 	    rm -f $(SPINPID); \
# 	    printf "\r\033[K"; \
# 	  fi; \
	}

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean: banner
	@rm -rf $(OBJ)
	@$(MAKE) -C $(LIBFTDIR) clean
	@echo "$(YELLOW)[CUB3D] Objects removed ✘$(RESET)"

fclean: banner
	@rm -rf $(OBJ)
	@echo "$(YELLOW)[CUB3D] Objects removed ✘$(RESET)"
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFTDIR) fclean
	@echo "$(RED)[CUB3D] Executable removed ✘$(RESET)"

re: banner fclean all