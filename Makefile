C_STANDART = \033[0m
C_GRAS = \033[1m
C_SOULIGN = \033[4m
C_CLIGN = \033[5m
C_SURLIGN = \033[7m
C_BLACK = \033[30m
C_RED = \033[31m
C_GREEN = \033[32m
C_YELLOW = \033[33m
C_BLUE = \033[34m
C_PINK = \033[35m
C_CYAN = \033[36m
C_GREY = \033[37m

NAME = Matches

CC = gcc -Wall -Wextra -Werror

SRC = main.c start_game.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME):
	@ make -C lib/ft_printf
	@ $(CC) $(addprefix src/, $(SRC)) -I inc lib/ft_printf/libftprintf.a -o bin/$(NAME)
	@ echo -e "\033[0m==\tCompilation $(NAME)\t\t\033[1;32mDONE$(C_STANDART)"

clean :
	@ make clean -C lib/ft_printf
	@ echo -e "\033[0m==\tClean $(NAME)\t\t\t\033[1;32mDONE$(C_STANDART)"

fclean :
	@ make fclean -C lib/ft_printf
	@ rm -f bin/$(NAME)
	@ echo -e "\033[0m==\tFclean $(NAME)\t\t\t\033[1;32mDONE$(C_STANDART)"

re: fclean all

test: re
	./bin/$(NAME)