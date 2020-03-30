##
## EPITECH PROJECT, 2020
## Makefile
## File description:
## Makefile
##

SRC_NO_TEST	=	src/main.c							\
				src/mysh.c

SRC_TEST	=	src/minishell.c						\
				src/print_command_prompt.c			\
				src/get_path_to_executable.c		\
				src/find_binary_in_path.c			\
				src/find_var_env.c					\
				src/get_var_value.c					\
				src/create_variable.c				\
				src/error.c							\
				src/sigint_handler.c				\
				src/builtin_functions.c				\
				src/builtin/cd.c					\
				src/builtin/env.c					\
				src/builtin/exit.c					\
				src/builtin/setenv.c				\
				src/builtin/unsetenv.c				\
				src/parsing/parse_command_line.c	\
				src/parsing/create_arg.c			\
				src/parsing/remove_quotes.c

SRC			=	$(SRC_NO_TEST) $(SRC_TEST)

CFLAGS		=	-I./include/ -Wall -Wextra

LIB			=	-L./lib -lmy

OBJ			=	$(SRC:.c=.o)

NAME		=	mysh

all:	$(NAME)

lib:
	make -s -C ./lib/my

$(NAME):	lib $(OBJ)
	gcc -o $(NAME) $(OBJ) $(LIB)
	rm -f $(OBJ)

tests_run:	lib
	@find . -name "*.gc*" -delete
	gcc -o unit_tests $(SRC_TEST) tests/*.c $(LIB) $(CFLAGS) --coverage -lcriterion
	./unit_tests
	rm -f unit_tests test*.gc*
	mkdir -p coverage
	mv *.gc* coverage/

debug:	lib
	gcc -g -o $(NAME) $(SRC) lib/my/*.c $(CFLAGS)

clean:
	rm -f $(OBJ)
	rm -f unit_tests *.gc*

fclean:	clean
	rm -f $(NAME)

re:	fclean all

.PHONY:	all lib tests_run debug clean fclean re
