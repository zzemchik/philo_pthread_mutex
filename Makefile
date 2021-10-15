NAME = philosophers
LIBSDIR = .


SOURCES = source/chek_death.c source/eat_philo.c source/exit.c source/init_philo.c source/look_for_eat.c \
source/main.c source/pars_param.c source/som_functions.c 

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