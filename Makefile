NAME	= minishell
CC		= cc
CFLAGS	= -Wall -Werror -Wextra
DFLAGS	= -g

// correct this later
ifeq ($(shell uname -s),Darwin)
	DFLAGS += -gdwarf-4 -gstrict-dwarf
	RL_INC = -I/opt/homebrew/opt/readline/include
	RL_LIB = -L/opt/homebrew/opt/readline/lib -lreadline
else ifeq ($(shell uname -s),Linux)
	RL_INC = -I/usr/include/readline
	RL_LIB = -lreadline
endif

TOKENIZE_TEST_SRCS = \
	$(wildcard src/tokenizer/*.c) \
	tests/test_tokenize.c \
	src/crash.c \
	src/print.c \
	libft/libft.a

SIGNAL_TEST_SRCS = \
	$(wildcard src/signals/*.c) \
	src/main.c

all: $(NAME)

tests: libft/libft.a
	@mkdir -p tests/out
	$(CC) $(CFLAGS) $(DFLAGS) $(TOKENIZE_TEST_SRCS) -o tests/out/tokenize.out

$(NAME): libft/libft.a
	$(CC) $(CFLAGS) $(SIGNAL_TEST_SRCS) $(RL_INC) $(RL_LIB) -o $(NAME)

libft/libft.a:
	@make -C libft
clean:
	rm -f *.o
fclean: clean
	rm -f $(NAME)
re: fclean all

.PHONY: all clean fclean re tests