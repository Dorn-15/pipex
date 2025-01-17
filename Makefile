NAME = pipex

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS = pipex.c \
		cmd.c \
		error.c \
		op-cl.c \
		process.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) ./libft/libft.a

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re