NAME = minishell
SRCS = 

OBJS = $(SRCS:.c=.o)

OBJ_DIR = obj

SRC_DIR = srcs

OBJS_FILES = $(addprefix $(OBJ_DIR)/, $(OBJS))

CC = cc
CFLAGS = -Wall -Wextra -Werror
LFLAGS = -lft -Llibft

LIBFT = libft/libft.a

all : $(NAME)

bonus : $(BONUS_NAME)

$(LIBFT) :
	make -C libft
	cp libft/$(LIBFT) $(LIBFT)

$(OBJ_DIR) :
	mkdir -p $(OBJ_DIR)
$(BNS_OBJ_DIR) :
	mkdir -p $(BNS_OBJ_DIR)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@
$(BNS_OBJ_DIR)/%.o : $(BNS_SRC_DIR)/%.c | $(BNS_OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME) : $(OBJS_FILES) $(LIBFT)
	$(CC) $(CFLAGS) $(LFLAGS) $(OBJS_FILES) -o $(NAME)

$(BONUS_NAME) : $(BNS_OBJS_FILES) $(LIBFT)
	$(CC) $(CFLAGS) $(LIBFT) $(BNS_OBJS_FILES) -o $(BONUS_NAME)

clean :
	make -C libft clean
	rm -rf $(OBJ_DIR)
	rm -rf $(BNS_OBJ_DIR)
.PHONY : clean

fclean : clean
	rm -rf libft/$(LIBFT)
	rm -rf $(LIBFT)
	rm -rf $(NAME)
	rm -rf $(BONUS_NAME)
.PHONY : fclean

re : fclean
	make all
.PHONY : re