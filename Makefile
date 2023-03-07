NAME = minishell
SRCS = main.c \
	   /parse/parse_cmd.c \
	   /parse/parse_env.c \
	   /parse/parse_file.c \
	   /parse/parse_option.c \
	   /parse/parse_util.c \
	   /execution/create_process.c \
	   /execution/execute_process.c \
	   /execution/get_command.c \
	   /execution/here_doc.c \
	   /execution/process_util.c \


OBJS = $(SRCS:.c=.o)

OBJ_DIR = obj

OBJ_DIRS = obj/parse \
		   obj/execution \
		   obj/builtin \
		   obj/env \
		   obj/error 

SRC_DIR = src

OBJS_FILES = $(addprefix $(OBJ_DIR)/, $(OBJS))

CC = cc
CFLAGS = -Wall -Wextra -Werror
LFLAGS = -lft -Llibft

LIBFT = libft/libft.a

all : $(NAME)

$(LIBFT) :
	make -C src/libft

$(OBJ_DIRS) :
	mkdir -p $(OBJ_DIRS)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c | $(OBJ_DIRS)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME) : $(OBJS_FILES) $(LIBFT)
	$(CC) $(CFLAGS) $(LFLAGS) $(OBJS_FILES) -o $(NAME)

clean :
	make -C libft clean
	rm -rf $(OBJ_DIRS)
.PHONY : clean

fclean : clean
	rm -rf $(LIBFT)
	rm -rf $(NAME)
.PHONY : fclean

re : fclean
	make all
.PHONY : re