NAME = philosophers

CC = cc

FLAGS = -Wall -Wextra -Werror -g

SRCS = philosophers.c\
philo_helpers.c\
struct_init.c\

OBJS := $(SRCS:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJS)
		cc -o $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@ -I./

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f$(NAME)

re: fclean all

.PHONY: all clean fclean re