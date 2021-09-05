NAME = philosophers
LIBSDIR = .


SOURCES = chek_death.c eat_philo.c exit.c init_philo.c look_for_eat.c \
main.c pars_param.c som_functions.c 

OSOURCE= $(SOURCES:.c=.o)

FLAGS = -Wall -Werror -Wextra
all: $(NAME)
%.o: %.c
	gcc -c $< $(FLAGS) -o $@ -I

$(NAME): $(OSOURCE)
	gcc -o $(NAME) $(OSOURCE) -I

clean:
	@rm -rf $(OSOURCE)

fclean: clean
	@rm -rf $(NAME)
re: fclean all

.PHONY: clean fclean all