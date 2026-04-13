NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror

RL_INC = -I/opt/homebrew/opt/readline/include
RL_LIB = -L/opt/homebrew/opt/readline/lib -lreadline

SRCS = signals.c main.c

all: $(NAME)

$(NAME):
	$(CC) $(CFLAGS) $(SRCS) $(RL_INC) $(RL_LIB) -o $(NAME)

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
