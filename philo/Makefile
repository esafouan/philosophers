NAME = philo
SRC =	checker.c \
		gettime.c \
		parsing.c \
		routine.c \
		main.c \

OBJ = ${SRC:.c=.o}
CFLAGS = -Wall -Werror -Wextra
CC = gcc

all: $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
clean:
	rm -rf $(OBJ)
fclean:
	rm -rf $(OBJ) $(NAME)
re: fclean all