# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/17 11:11:52 by lud-adam          #+#    #+#              #
#    Updated: 2025/04/14 16:39:02 by ppontet          ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME := pipex.a

SRC_DIR := src/
OBJ_DIR := obj/
LIBFT_DIR := ../libft/
DEP_DIR := dep/
INC_DIR := include/

SRC = \
	$(SRC_DIR)execution.c \
	$(SRC_DIR)free.c \
	$(SRC_DIR)functions_utils.c \
	$(SRC_DIR)get_path.c \
	$(SRC_DIR)main.c \
	$(SRC_DIR)process.c

LIBFT_INC = $(LIBFT_DIR)inc/libft.h  

OBJ := $(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)
DEP := $(OBJ:$(OBJ_DIR)%.o=$(DEP_DIR)%.d)

MAKE := make -j
CC := cc
CFLAGS := -Wall -Wextra -Werror
INC := -I$(INC_DIR) -I/usr/include -I$(LIBFT_DIR)inc
LIBFT := $(LIBFT_DIR)libft.a
P_PIPEX_LIB := lib/

all: $(P_PIPEX_LIB)libpipex.a

$(P_PIPEX_LIB)libpipex.a: $(OBJ)
	@mkdir -p $(P_PIPEX_LIB)
	@if ar -rcs $(P_PIPEX_LIB)libpipex.a $^; then \
		echo "$(Green)Creating library $@$(Color_Off)"; \
	else \
		echo "$(Red)Error creating $@$(Color_Off)"; \
	fi

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INC_DIR)pipex.h Makefile $(LIBFT)
	@mkdir -p $(dir $@)
	@if $(CC) $(CFLAGS) $(INC) -MMD -MP -c $< -o $@; then \
		echo "$(Cyan)Compiling $<$(Color_Off)"; \
	else \
		echo "$(Red)Error creating $@$(Color_Off)"; \
	fi

$(LIBFT): force
	$(MAKE) -C $(LIBFT_DIR)

force: 

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -rf $(OBJ_DIR) $(DEP_DIR)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -fr lib/ 
	rm -rf $(NAME)

re: fclean $(NAME)

Color_Off=\033[0m       # Text Reset
Cyan=\033[0;36m
Green=\033[0;32m


-include $(DEP)

.PHONY: all clean fclean re
