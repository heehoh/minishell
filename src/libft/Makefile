NAME = libft.a
SRCS = ft_atoi.c \
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
	$(AR) crs $(NAME) $(OBJS)

%.o : %.c
	$(CC) -c $(CFLAGS) $< -o $@

clean :
	rm -f $(OBJS)

.PHONY : clean

fclean : clean
	rm -f $(NAME)

.PHONY : fclean

re :
	make fclean
	make all

.PHONY : re
