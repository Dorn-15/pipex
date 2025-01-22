NAME = pipex

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS = pipex.c \
		cmd.c \
		close.c \
		process.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) libft
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) ./libft/libft.a

libft:
	make -C ./libft

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	make -C ./libft clean

fclean: clean
	rm -f $(NAME)
	make -C ./libft fclean

re: fclean all

.PHONY: all clean fclean re libft
