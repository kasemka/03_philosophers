NAME = philo

SRC = philo.c\
ft_atoi.c\
malloc_fail.c

HEADER = philo.h
OBJ = $(SRC:.c=.o)

CC = gcc
FLAGS = -Wall -Wextra -Werror

%.o: %.c $(HEADER)
		$(CC) $(FLAGS) -c -o $@ $<

$(NAME): $(OBJ)
		$(CC) $(FLAGS) -o $@ $^ 

all: $(NAME)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean re