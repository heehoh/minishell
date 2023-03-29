NAME = minishell
SRCS = main.c \
	   init_setting.c \
	   /parse/parse_cmd.c \
	   /parse/parse_env.c \
	   /parse/parse_exit_code.c \
	   /parse/parse_file.c \
	   /parse/parse_option.c \
	   /parse/parse_util.c \
	   /parse/delete_quote.c \
	   /execution/create_process.c \
	   /execution/execute_process.c \
	   /execution/get_command.c \
	   /execution/here_doc.c \
	   /execution/process_util.c \
	   /execution/open_file.c \
	   /error/print_error.c \
	   /error/print_error2.c \
	   /error/syntax_error.c \
	   /builtin/builtin_cd.c \
	   /builtin/builtin_echo.c \
	   /builtin/builtin_env.c \
	   /builtin/builtin_exit.c \
	   /builtin/builtin_export.c \
	   /builtin/builtin_pwd.c \
	   /builtin/builtin_unset.c \
	   /builtin/is_builtin.c \
	   /builtin/builtin_error.c \
	   /env/env.c \
	   /signal/signal.c

OBJS = $(SRCS:.c=.o)

OBJ_DIR = obj

OBJ_DIRS = obj/parse \
		   obj/execution \
		   obj/builtin \
		   obj/env \
		   obj/error \
		   obj/signal

SRC_DIR = src

OBJS_FILES = $(addprefix $(OBJ_DIR)/, $(OBJS))

CC = cc
CFLAGS = -Wall -Wextra -Werror 
#-g -fsanitize=address
LFLAGS = -lft -Llibft -lreadline \
		 -L $(HOME)/goinfre/.brew/opt/readline/lib 

INCLUDE = $(HOME)/goinfre/.brew/opt/readline/include

LIBFT = libft/libft.a

all : $(NAME)

$(LIBFT) :
	@make -C libft

$(OBJ_DIRS) :
	@mkdir -p $(OBJ_DIRS)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c | $(OBJ_DIRS)
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(INCLUDE)

$(NAME) : $(OBJS_FILES) $(LIBFT)
	@$(CC) $(CFLAGS) $(LFLAGS) $(OBJS_FILES) -o $(NAME)
	@echo "\033[31mmake minishell\033[0m"

clean :
	@make -C libft clean
	@rm -rf $(OBJ_DIR)
	@echo "\033[33mclean obj\033[0m"
.PHONY : clean

fclean : clean
	@rm -rf $(LIBFT)
	@rm -rf $(NAME)
	@echo "\033[33mremove minishell\033[0m"
.PHONY : fclean

re : fclean
	@make all
.PHONY : re
