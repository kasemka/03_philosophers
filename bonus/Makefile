NAME = philo_bonus

SRC = main.c\
parse.c\
msg_fail.c\
init_struct.c\
ft_atoi.c\
time_correct.c

HEADER = philo_bonus.h
OBJ = $(SRC:.c=.o)

CC = gcc
FLAGS = -Wall -Wextra -Werror

%.o: %.c $(HEADER)
		$(CC) -g $(FLAGS) -c -o $@ $<

$(NAME): $(OBJ)
		$(CC) -g $(FLAGS) -o $@ $^
		rm -f $(OBJ)

all: $(NAME)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean re
