NAME	= minishell
CC		= cc
CFLAGS	= -Wall -Werror -Wextra
DFLAGS	= -g -finstrument-functions

UNAME_S := $(shell uname -s)

INCLUDE = -I./include -I./libft/include
LIBS    = -L./libft -lft

ifeq ($(UNAME_S),Darwin)
	INCLUDE += -I/opt/homebrew/opt/readline/include
	LIBS    += -L/opt/homebrew/opt/readline/lib -lreadline
else ifeq ($(UNAME_S),Linux)
	INCLUDE += -I/usr/include/readline
	LIBS    += -L/usr/lib -lreadline
endif

# ========== minishell sources ==========
SRCS = \
	src/globals.c \
	src/crash.c \
	src/print.c \
	$(wildcard src/signals/*.c) \
	$(wildcard src/tokenizer/*.c) \
	$(wildcard src/parser/*.c) \
	$(wildcard src/dispatcher/*.c) \
	$(wildcard src/builtins/*.c) \
	$(wildcard src/shell/*.c)

MAIN = src/main.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(DFLAGS) $(INCLUDE) -c $< -o $@

$(NAME): libft/libft.a $(OBJS) src/main.o
	$(CC) $(CFLAGS) $(DFLAGS) $(OBJS) src/main.o $(INCLUDE) $(LIBS) -o $@

tests: libft/libft.a $(OBJS)
	$(CC) $(CFLAGS) $(DFLAGS) $(OBJS) tests/test_parse.c $(INCLUDE) $(LIBS) -o tests/test_parse
	$(CC) $(CFLAGS) $(DFLAGS) $(OBJS) tests/test_expand.c $(INCLUDE) $(LIBS) -o tests/test_expand
	$(CC) $(CFLAGS) $(DFLAGS) $(OBJS) tests/test_execve.c $(INCLUDE) $(LIBS) -o tests/test_execve
	$(CC) $(CFLAGS) $(DFLAGS) $(OBJS) tests/test_split_quotes.c $(INCLUDE) $(LIBS) -o tests/test_split_quotes

libft/libft.a:
	@make -C libft

clean:
	rm -f $(OBJS) src/main.o
	@make -C libft clean

clean_tests:
	rm -f tests/test_parse tests/test_expand tests/test_execve tests/test_split_quotes

fclean: clean clean_tests
	rm -f $(NAME)
	@make -C libft fclean

re: fclean all

.PHONY: all clean fclean re tests
