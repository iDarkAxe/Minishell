# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lud-adam <lud-adam@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/17 11:11:52 by lud-adam          #+#    #+#              #
#    Updated: 2025/03/26 13:34:29 by lud-adam         ###   ########.fr        #
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
	ar -rcs $(P_PIPEX_LIB)libpipex.a $^

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INC_DIR)pipex.h Makefile $(LIBFT)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC) -MMD -MP -c $< -o $@

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

-include $(DEP)

.PHONY: all clean fclean re
