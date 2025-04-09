.PHONY : all clean fclean re bonus clean-lib clean-bin clean-obj debug debug-cc debug-print
CC = cc
CFLAGS = -Wextra -Wall -Werror
DEPENDANCIES = -MMD -MP
NO_DIR = --no-print-directory
MAKE := $(MAKE) -j $(NO_DIR)
NAME = minishell_tests

# Debugging flags
CFLAGS_DEBUG = -Wall -Wextra -g3 -D DEBUG=1
CC_DEBUG = clang
CC_DEBUG_CFLAGS = -g3 -D DEBUG=1 -Weverything -Wno-padded -pedantic -O2 -Wwrite-strings -Wconversion -fsanitize=address -fsanitize=leak -Wno-suggest-override -Wno-suggest-destructor-override
#############################################################################################
#                                                                                           #
#                                         DIRECTORIES                                       #
#                                                                                           #
#############################################################################################
# Source directories
P_ROOT = ../

P_SRC = src/
P_PARSING = parsing_quotes_double/
P_FILE = file/
P_UNITY = unity/

P_OBJ = .obj/
P_TESTS_OBJS = $(P_TESTS).obj/

P_INC = inc/

P_INCS = \
	$(P_INC) \
	$(P_LIBFT)inc/ \
	$(P_PIPEX)include/ 

# Libraries directories
P_LIB = lib/
P_LIBFT = ../libft/
P_PIPEX = ../pipex/
P_LIB_PIPEX = ../pipex/lib/
#############################################################################################
#                                                                                           #
#                                           FILES                                           #
#                                                                                           #
#############################################################################################
# Headers
INC = \
	minishell.h

INCS = \
	-I $(P_ROOT)inc \
	-I $(P_ROOT)libft/inc \
	-I $(P_UNITY) \
	-I $(P_ROOT)pipex/include

# Source files
SRC = \
	main.c \

PARSING = \
	testing_parsing_quotes_double.c \
	tests_fx_printing.c \
	tests_pars_sing_fx1.c \
	tests_pars_sing_fx2.c \
	tests_pars_doub_fx1.c \
	tests_pars_doub_fx2.c

FILE = \
	testing_file.c \
	tests_file.c

UNITY_SRC = \
	unity.c

LIBS = \
	-L$(P_ROOT)libft -lft \
	-L$(P_ROOT)pipex/lib -lpipex \
	-L$(P_ROOT)lib -lminishell \
	-L$(P_ROOT)libft -lft \
	-lreadline

LIBFT = $(P_LIBFT)libft.a
PIPEX = $(P_LIB_PIPEX)libpipex.a
#############################################################################################
#                                                                                           #
#                                        MANIPULATION                                       #
#                                                                                           #
#############################################################################################
SRCS = \
	$(addprefix $(P_SRC), $(SRC)) \
	$(addprefix $(P_SRC)$(P_PARSING), $(PARSING)) \
	$(addprefix $(P_SRC)$(P_FILE), $(FILE)) \

UNITY_SRCS = \
	$(addprefix $(P_UNITY), $(UNITY_SRC)) \

# List of object files (redirect to P_OBJ)
OBJS = \
	$(patsubst $(P_SRC)%.c, $(P_OBJ)%.o, $(SRCS)) \
	$(P_OBJ)$(UNITY_SRCS:%.c=%.o)

P_OBJS = $(subst $(P_SRC), $(P_OBJ), $(SRCS))

# List of depedencies
DEPS = $(OBJS:%.o=%.d) $(OBJS_TEST:%.o=%.d)

# List of header files
INCS = \
	-I $(P_ROOT)inc \
	-I inc \
	-I $(P_ROOT)libft/inc \
	-I $(P_UNITY) \
	-I $(P_ROOT)pipex/include

# Librairies
LIBS = \
	-L$(P_ROOT)libft -lft \
	-L$(P_ROOT)pipex/lib -lpipex \
	-L$(P_ROOT)lib -lminishell \
	-L$(P_ROOT)libft -lft \
	-lreadline

#############################################################################################
#                                                                                           #
#                                          RULES                                            #
#                                                                                           #
#############################################################################################
all:
	@$(MAKE) $(NAME)

# Create $(NAME) executable
all: $(NAME)

$(NAME): $(OBJS)
	@$(MAKE) -C $(P_ROOT)
	@$(MAKE) -C ../ lib/libminishell.a
	@$(MAKE) -C $(P_ROOT)libft
	@$(MAKE) -C $(P_ROOT)pipex
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

# Custom rule to compilate all .c with there path
$(P_OBJ)%.o: $(P_SRC)%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(DEPENDENCIES) $(INCS) -c $< -o $@

$(P_OBJ)$(P_UNITY)%.o: $(P_UNITY)%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(DEPENDENCIES) $(INCS) -c $< -o $@

force:

#############################################################################################
#                                                                                           #
#                                      Other RULES                                          #
#                                                                                           #
#############################################################################################
# Rules for clean up
clean:
	rm -rfd $(P_OBJ)
	rm -rfd $(P_TESTS_OBJS)
	rm -rfd $(OBJS)
	rm -rfd $(OBJS_TEST)
	rm -rfd $(DEPS)

clean-lib:
	rm -rfd $(P_LIB)
	make -C $(P_LIBFT) fclean
	make -C $(P_PIPEX) fclean

clean-bin:
	rm -f $(NAME)
	rm -f $(NAME)

clean-obj:
	@$(MAKE) clean

fclean:
	@$(MAKE) clean-obj
	@$(MAKE) clean-lib
	@$(MAKE) clean-bin

re:
	@$(MAKE) fclean
	@$(MAKE) all

# Aliases
clear: clean
fclear: fclean
flcean: fclean
flcear: fclean

#############################################################################################
cat -A Makefile | nl
#                                                                                           #
#                                           DEBUG                                           #
#                                                                                           #
#############################################################################################
# Debugging rules
debug:
	@$(MAKE) $(NAME) CFLAGS="$(CFLAGS_DEBUG)"

debug-checker:
	@$(MAKE) checker CFLAGS="$(CFLAGS_DEBUG)"

debug-cc:
	@$(MAKE) $(NAME) CFLAGS="$(CC_DEBUG_CFLAGS)" CC="$(CC_DEBUG)"

# Debugging print
debug-print:
	@$(MAKE) debug-print-project
	@$(MAKE) debug-print-separator

debug-print-separator:
	@echo ""
	@echo "$(On_Yellow)____________________$(Color_Off)"
	@echo ""

define check_var
	@if [ "$(strip $(1))" = "" ]; then \
		echo "$(Red)No $(2) found$(Color_Off)"; \
	else \
		echo "$(Red)$(2): \n\t$(Blue)$(1)$(Color_Off)"; \
	fi
endef

debug-print-project:
	$(call check_var,$(NAME),"Project")
	$(call check_var,$(SRCS),"SRCS")
	$(call check_var,$(OBJS),"OBJS")
	$(call check_var,$(INCS),"INCS")
	$(call check_var,$(LIBS),"LIBS")
	@$(MAKE) debug-print-separator
	$(call check_var,$(SRCS_TEST),"SRCS_TEST")
	$(call check_var,$(OBJS_TEST),"OBJS_TEST")


#############################################################################################
#                                                                                           #
#                                         COSMETIC                                          #
#                                                                                           #
#############################################################################################
# Reset
Color_Off=\033[0m       # Text Reset

# Regular Colors
Black=\033[0;30m
Red=\033[0;31m
Green=\033[0;32m
Yellow=\033[0;33m
Blue=\033[0;34m

# Background
On_Yellow=\033[43m

-include $(DEPS)% 
