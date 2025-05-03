.PHONY : all clean fclean re bonus clean-lib clean-bin clean-obj debug debug-cc debug-print
CC = cc
CFLAGS = -Wextra -Wall -Werror
DEPENDANCIES = -MMD -MP
NO_DIR = --no-print-directory
MAKE := $(MAKE) -j $(NO_DIR)
NAME_TEST = test
NAME = minishell

# Debugging flags
CFLAGS_DEBUG = -Wall -Wextra -g3 -D DEBUG=1
CC_DEBUG = clang
CC_DEBUG_CFLAGS = -g3 -D DEBUG=1 -Weverything -Wno-padded -pedantic -O2 -Wwrite-strings -Wconversion -fsanitize=address -fsanitize=leak -Wno-suggest-override -Wno-suggest-destructor-override -Wno-incompatible-pointer-types-discards-qualifiers -Wno-disabled-macro-expansion
#############################################################################################
#                                                                                           #
#                                         DIRECTORIES                                       #
#                                                                                           #
#############################################################################################
# Source directories
P_SRC = src/
P_GARBAGE = garbage/
P_LEXER = lexer/
P_PARSING = parsing/
P_FILE = file/
P_BUILTINS = builtins/
P_ENV = env/
P_EXEC = exec/

P_PIPEX = pipex/src/
P_TESTS = tests/

P_OBJ = .obj/

P_INC = inc/
P_INCS = \
	$(P_INC) \
	$(P_LIBFT)inc/ \
	$(P_PIPEX)include/ \
	$(P_PIPEX)include/

# Libraries directories
P_LIB = lib/
P_LIBFT = libft/
P_PIPEX = pipex/
P_LIB_PIPEX = pipex/lib/
P_GET_NEXT_LINE = get_next_line/
#############################################################################################
#                                                                                           #
#                                           FILES                                           #
#                                                                                           #
#############################################################################################
# Headers
INC = \
	minishell.h \
	garbage.h \
	file.h \
	env.h \
	garbage.h \
	file.h

# Source files
SRC = \
	main.c \
	prompt.c \
	signals.c \
	ft_print_fd.c \
	ft_free.c \
	minishell.c \
	token-utils.c \
	read_context.c \

# builtins.c

GARBAGE = \
	garbage.c \
	garbage_stack.c \
	garbage_utils.c

LEXER = \
	lexer.c \
	lexer-utils.c \
	tokens.c \

PARSING = \
	parsing.c \
	expand_home.c \
	parsing_quotes_double.c \

FILE = \
	file.c \
	file_build.c \
	file_print.c \
	file_verify_access.c \
	heredoc.c \
	tmp_generator.c \
	ft_file_tokens.c \
	file-general.c \

BUILTINS = \
	ft_exit.c \
	ft_echo.c \
	ft_which.c \
	ft_cd.c \
	ft_env.c \

ENV = \
	get_env.c \
	functions_utils.c \
	functions_utils_env.c 

EXEC = \
	command-utils.c \
	exec.c \
	exec_extern.c \
	ft_dups.c \
	exec_in_forks.c

LIBS = \
	-L$(P_LIB_PIPEX) -lpipex \
	-L$(P_LIBFT) -lft \
	-L$(P_GET_NEXT_LINE) -lgnl \
	-L$(P_LIBFT) -lft \
	-lreadline \

LIBFT = $(P_LIBFT)libft.a
PIPEX = $(P_LIB_PIPEX)libpipex.a
GET_NEXT_LINE = $(P_GET_NEXT_LINE)libgnl.a
#############################################################################################
#                                                                                           #
#                                        MANIPULATION                                       #
#                                                                                           #
#############################################################################################
SRCS =	\
	$(addprefix $(P_SRC), $(SRC)) \
	$(addprefix $(P_SRC)$(P_GARBAGE), $(GARBAGE)) \
	$(addprefix $(P_SRC)$(P_LEXER), $(LEXER)) \
	$(addprefix $(P_SRC)$(P_PARSING), $(PARSING)) \
	$(addprefix $(P_SRC)$(P_FILE), $(FILE)) \
	$(addprefix $(P_SRC)$(P_BUILTINS), $(BUILTINS)) \
	$(addprefix $(P_SRC)$(P_ENV), $(ENV)) \
	$(addprefix $(P_SRC)$(P_EXEC), $(EXEC)) \

# List of object files (redirect to P_OBJ)
OBJS = $(subst $(P_SRC), $(P_OBJ), $(SRCS:.c=.o))
P_OBJS = $(subst $(P_SRC), $(P_OBJ), $(SRCS))

# List of depedencies
DEPS = $(OBJS:%.o=%.d) $(OBJS_TEST:%.o=%.d)

# List of header files
INCS = $(addprefix $(P_INC), $(INC)) \
		$(P_LIBFT)inc/libft.h \
		$(P_PIPEX)include/pipex.h
		
#############################################################################################
#                                                                                           #
#                                          RULES                                            #
#                                                                                           #
#############################################################################################
all:
	@$(MAKE) $(NAME)

# Create $(NAME) executable
$(NAME): $(OBJS) $(INCS) $(LIBFT) $(PIPEX) $(GET_NEXT_LINE)
	@if $(CC) $(CFLAGS) $(DEPENDANCIES) $(DEBUG_STATE) -I $(P_INC) -I $(P_LIBFT)inc -I $(P_PIPEX)include -I $(P_GET_NEXT_LINE) -o $(NAME) $(OBJS) $(LIBS); then \
		echo "$(Green)Creating executable $@$(Color_Off)"; \
	else \
		echo "$(Red)Error creating $@$(Color_Off)"; \
	fi

# Custom rule to compilate all .c with there path
$(P_OBJ)%.o: $(P_SRC)%.c $(INCS)
	@mkdir -p $(dir $@)
	@if $(CC) $(CFLAGS) $(DEPENDANCIES) $(DEBUG_STATE) -I $(P_INC) -I $(P_LIBFT)inc -I $(P_PIPEX)include -I $(P_GET_NEXT_LINE) -c $< -o $@; then \
		echo "$(Cyan)Compiling $<$(Color_Off)"; \
	else \
		echo "$(Red)Error creating $@$(Color_Off)"; \
	fi

force:

$(LIBFT): force
	@$(MAKE) -C $(P_LIBFT)

$(PIPEX): force
	@$(MAKE) -C $(P_PIPEX)

$(GET_NEXT_LINE): force
	@$(MAKE) -C $(P_GET_NEXT_LINE)

$(P_LIB)libminishell.a: $(OBJS) $(INCS) $(LIBFT) $(PIPEX)
	@mkdir -p $(dir $@)
	@echo "$(Green)Creating library $@$(Color_Off)"
	@ar -rcs $@ $(OBJS)

$(NAME_TEST): force
	@$(MAKE) -C $(P_TESTS)

############################################################################################
#                                                                                           #
#                                      Other RULES                                          #
#                                                                                           #
#############################################################################################
# Rules for clean up
clean:
	rm -rfd $(P_OBJ)
	rm -rfd $(OBJS)
	rm -rfd $(DEPS)

clean-lib:
	rm -rfd $(P_LIB)
	@$(MAKE) -C $(P_LIBFT) fclean
	@$(MAKE) -C $(P_PIPEX) fclean
	@$(MAKE) -C $(P_GET_NEXT_LINE) fclean
	@$(MAKE) -C tests fclean

clean-bin:
	rm -f $(NAME)
	rm -f $(NAME_TEST)

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
	@$(MAKE) $(NAME) CFLAGS="$(CC_DEBUG_CFLAGS)" CC="$(CC_DEBUG)" Cyan="$(Yellow)" Green="$(Purple)"

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
Purple=\033[0;35m
Cyan=\033[0;36m
White=\033[0;37m

# Background
On_Black=\033[40m
On_Red=\033[41m
On_Green=\033[42m
On_Yellow=\033[43m
On_Blue=\033[44m
On_Purple=\033[45m
On_Cyan=\033[46m
On_White=\033[47m

-include $(DEPS)% 
