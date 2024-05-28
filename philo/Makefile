NAME = philo

CC = cc

FLAGS = -Wall -Wextra -Werror -g

SRCS = philosophers.c\
philo_helpers.c\
struct_init.c\

OBJS := $(SRCS:%.c=%.o)

RM = rm -rf

all: $(NAME)

$(NAME): $(OBJS)
		cc -o $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@ -I./

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

test:	all
			valgrind ./philosophers 10 200 50 200

re: fclean all

.PHONY: all clean fclean re

run:	all
			./$(NAME) 3 650 200 100 5 > file