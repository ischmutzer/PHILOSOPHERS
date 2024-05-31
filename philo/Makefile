NAME = philo

CC = cc

FLAGS = -Wall -Wextra -Werror -g

HELP = helper_functions/

INIT = init/

PHILOS = philos/

MONITOR = monitor/

SRCS = philosophers.c\
$(HELP)checker_atoi.c\
$(HELP)clean_up.c\
$(HELP)helper_functions.c\
$(HELP)monitor_helper.c\
$(HELP)routine_helper.c\
$(INIT)struct_init.c\
$(MONITOR)monitor.c\
$(PHILOS)lone_philo.c\
$(PHILOS)routine.c

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