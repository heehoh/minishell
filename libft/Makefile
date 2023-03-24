NAME = libft.a
SRCS = ft_atoi.c \
	   ft_itoa.c \
	   ft_isalnum.c \
	   ft_isalpha.c \
	   ft_is_space.c \
	   ft_split.c \
	   ft_strdup.c \
	   ft_strjoin.c \
	   ft_strlen.c \
	   ft_strncmp.c \
	   get_next_line.c \
	   get_next_line_utils.c

OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror


all : $(NAME)

$(NAME) : $(OBJS)
	@$(AR) crs $(NAME) $(OBJS)
	@echo "\033[31mmake libft\033[0m"

%.o : %.c
	@$(CC) -c $(CFLAGS) $< -o $@

clean :
	@rm -f $(OBJS)
.PHONY : clean

fclean : clean
	@rm -f $(NAME)
.PHONY : fclean

re : fclean
	@make all
.PHONY : re
