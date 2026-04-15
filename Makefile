NAME	= minishell
CC		= cc
CFLAGS	= -Wall -Werror -Wextra
DFLAGS	= -g

UNAME_S := $(shell uname -s)
INCLUDE = -I./include
LIBS = -L./libft -lft

ifeq ($(UNAME_S),Darwin)
	INCLUDE += -I/opt/homebrew/opt/readline/include
	LIBS += -L/opt/homebrew/opt/readline/lib -lreadline
else ifeq ($(UNAME_S),Linux)
	INCLUDE += -I/usr/include/readline
	LIBS += -L/usr/lib -lreadline
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
	$(CC) $(CFLAGS) $(SIGNAL_TEST_SRCS) $(INCLUDE) $(LIBS) -o $(NAME)

libft/libft.a:
	@make -C libft
clean:
	rm -f *.o
fclean: clean
	rm -f $(NAME)
re: fclean all

.PHONY: all clean fclean re tests
