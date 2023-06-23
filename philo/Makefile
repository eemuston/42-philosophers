NAME = philo

SRC = philosophers.c errors.c utils.c init.c simulation.c utils_two.c monitoring.c

OBJ = philosophers.o errors.o utils.o init.o simulation.o utils_two.o monitoring.o

FLAGS = -pthread -Wall -Wextra -Werror -O2 

all: $(NAME)

%.o:	%.c
		cc $(FLAGS) -I. -c $< -o $@

$(NAME): $(OBJ)
		cc $(FLAGS) $(OBJ) -o $(NAME)
clean:
		rm -f $(OBJ)
fclean: clean
		rm -f $(NAME) clean
re: fclean all