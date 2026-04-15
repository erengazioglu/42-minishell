NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Darwin)
	RL_INC = -I/opt/homebrew/opt/readline/include
	RL_LIB = -L/opt/homebrew/opt/readline/lib -lreadline
else ifeq ($(UNAME_S),Linux)
	RL_INC =
	RL_LIB = -lreadline
endif

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
