##
## EPITECH PROJECT, 2020
## Makefile
## File description:
## Makefile
##

SRC_NO_TEST			=	src/main.c							\
						src/mysh.c

SRC_TEST			=	src/minishell.c						\
						src/exec_shell_commands.c			\
						src/exec_piped_commands.c			\
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
						src/parsing/change_fd.c				\
						src/parsing/check_line_validity.c	\
						src/parsing/get_character_index.c	\
						src/parsing/parse_input.c

SRC					=	$(SRC_NO_TEST) $(SRC_TEST)

CFLAGS				=	-Wall -Wextra

CPPFLAGS			=	-I./include/

override LDFLAGS	+=	-L./lib

override LDLIBS		+=	-lmy

OBJ					=	$(SRC:.c=.o)

NAME				=	mysh

all:	$(NAME)

$(NAME):	CFLAGS += -O2
$(NAME):	$(LDLIBS) $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LDFLAGS) $(LDLIBS)

-lmy:
	$(MAKE) -s -C ./lib/my

tests_run:	CFLAGS += --coverage
tests_run:	LDLIBS += -lcriterion
tests_run:	$(LDLIBS)
	@find -name "*.gc*" -delete
	$(CC) -o unit_tests $(SRC_TEST) tests/*.c $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(LDLIBS)
	-./unit_tests
	$(RM) unit_tests test*.gc*
	mkdir -p coverage
	mv *.gc* coverage/

debug:	CFLAGS += -g
debug:	$(LDLIBS)
	$(CC) -o $(NAME) $(SRC) $(LDFLAGS) $(LDLIBS) $(CFLAGS) $(CPPFLAGS)

clean:
	$(RM) $(OBJ)
	$(RM) unit_tests *.gc*

fclean:	clean
	rm -f $(NAME)

re:	fclean all

.PHONY:	all -lmy tests_run debug clean fclean re
