# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pdaskalo <pdaskalo@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/15 13:42:57 by pdaskalo          #+#    #+#              #
#    Updated: 2025/09/04 16:08:43 by pdaskalo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                                LIBFT MAKEFILE                                #
# **************************************************************************** #

RESET	= \033[0m
GREEN	= \033[1;32m
BLUE	= \033[1;34m
RED		= \033[1;31m
YELLOW	= \033[1;33m

NAME	= libft.a
CC		= cc
CFLAGS	= -Wall -Wextra -Werror -Iinclude
AR		= ar rcs
RM		= rm -f

SRC_DIR	= src

# ------------------------------------------------------------------------------
# Source Files
# ------------------------------------------------------------------------------

# Error Handling
SRC_ERROR := \
	$(SRC_DIR)/error/ft_freearr.c \
	$(SRC_DIR)/error/ft_putperror.c

# Char Utilities
SRC_CHAR := \
	$(SRC_DIR)/char/ft_isalnum.c \
	$(SRC_DIR)/char/ft_isalpha.c \
	$(SRC_DIR)/char/ft_isascii.c \
	$(SRC_DIR)/char/ft_isdigit.c \
	$(SRC_DIR)/char/ft_isprint.c \
	$(SRC_DIR)/char/ft_isspace.c \
	$(SRC_DIR)/char/ft_minmax.c \
	$(SRC_DIR)/char/ft_tolower.c \
	$(SRC_DIR)/char/ft_toupper.c

# String Functions
SRC_STRING := \
	$(SRC_DIR)/string/ft_strchr.c \
	$(SRC_DIR)/string/ft_strcmp.c \
	$(SRC_DIR)/string/ft_strdup.c \
	$(SRC_DIR)/string/ft_strilen.c \
	$(SRC_DIR)/string/ft_striteri.c \
	$(SRC_DIR)/string/ft_strjoin.c \
	$(SRC_DIR)/string/ft_strlcat.c \
	$(SRC_DIR)/string/ft_strlcpy.c \
	$(SRC_DIR)/string/ft_strlen.c \
	$(SRC_DIR)/string/ft_strmapi.c \
	$(SRC_DIR)/string/ft_strncmp.c \
	$(SRC_DIR)/string/ft_strndup.c \
	$(SRC_DIR)/string/ft_strnstr.c \
	$(SRC_DIR)/string/ft_strrchr.c \
	$(SRC_DIR)/string/ft_strtrim.c \
	$(SRC_DIR)/string/ft_substr.c

# Memory Functions
SRC_MEMORY := \
	$(SRC_DIR)/memory/ft_bzero.c \
	$(SRC_DIR)/memory/ft_calloc.c \
	$(SRC_DIR)/memory/ft_memchr.c \
	$(SRC_DIR)/memory/ft_memcmp.c \
	$(SRC_DIR)/memory/ft_memcpy.c \
	$(SRC_DIR)/memory/ft_memmove.c \
	$(SRC_DIR)/memory/ft_memset.c

# Conversion
SRC_CONV := \
	$(SRC_DIR)/conv/ft_atoi.c \
	$(SRC_DIR)/conv/ft_atol.c \
	$(SRC_DIR)/conv/ft_atoll.c \
	$(SRC_DIR)/conv/ft_itoa.c

# Array Utilities
SRC_ARR := \
	$(SRC_DIR)/arr/ft_arrlen.c \
	$(SRC_DIR)/arr/ft_split.c \
	$(SRC_DIR)/arr/ft_strsilen.c \
	$(SRC_DIR)/arr/ft_strslen.c

# FD Functions
SRC_FD := \
	$(SRC_DIR)/fd/ft_putchar_fd.c \
	$(SRC_DIR)/fd/ft_putendl_fd.c \
	$(SRC_DIR)/fd/ft_putnbr_fd.c \
	$(SRC_DIR)/fd/ft_putstr_fd.c

# GNL
SRC_GNL := \
	$(SRC_DIR)/gnl/get_next_line.c

# Printf
SRC_PRINTF := \
	$(SRC_DIR)/printf/ft_printf.c \
	$(SRC_DIR)/printf/ft_fprintf.c \
	$(SRC_DIR)/printf/srcs/ft_put.c \
	$(SRC_DIR)/printf/srcs/ft_puthex.c \
	$(SRC_DIR)/printf/srcs/ft_functions.c \
	$(SRC_DIR)/printf/srcs/ft_fputhex.c \
	$(SRC_DIR)/printf/srcs/ft_fput.c

# ------------------------------------------------------------------------------
# Combine All Sources
# ------------------------------------------------------------------------------
SRCS := $(SRC_ERROR) $(SRC_CHAR) $(SRC_STRING) $(SRC_MEMORY) $(SRC_CONV) \
		$(SRC_ARR) $(SRC_FD) $(SRC_GNL) $(SRC_PRINTF)

OBJS := $(SRCS:.c=.o)

# ==============================================================================
# RULES
# ==============================================================================

SPINPID := .spinner.pid

all: $(NAME)

$(NAME): $(OBJS)
	@$(AR) $(NAME) $(OBJS)
	@$(MAKE)
	@printf "\n$(GREEN)[LIBFT] Compiled successfully ✔$(RESET)\n"

# $(NAME): $(OBJS)
# 	@$(AR) $(NAME) $(OBJS)
# 	@$(MAKE) --no-print-directory stop_spinner
# 	@printf "\n$(GREEN)[LIBFT] Compiled successfully ✔$(RESET)\n"

# Start the spinner once before any object is built
# $(OBJS): | start_spinner

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
# 	    printf "\r\033[K$(BLUE)[LIBFT] Compiling files%s$(RESET)" "$$dots"; \
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
# 	}

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJS)
	@echo "$(YELLOW)[LIBFT] Objects removed ✘$(RESET)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(RED)[LIBFT] Archive removed ✘$(RESET)"

re: fclean all