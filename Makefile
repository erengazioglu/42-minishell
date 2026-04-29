NAME	= minishell
CC		= cc
CFLAGS	= -Wall -Werror -Wextra
DFLAGS	= -g

UNAME_S := $(shell uname -s)

INCLUDE = -I./include
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
	src/main.c \
	src/globals.c \
	src/crash.c \
	src/print.c \
	$(wildcard src/signals/*.c) \
	$(wildcard src/tokenizer/*.c)

OBJS = $(SRCS:.c=.o)

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(DFLAGS) $(INCLUDE) -c $< -o $@

$(NAME): libft/libft.a $(OBJS)
	$(CC) $(CFLAGS) $(DFLAGS) $(OBJS) $(INCLUDE) $(LIBS) -o $@

libft/libft.a:
	@make -C libft

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)
	@make -C libft fclean

re: fclean all

.PHONY: all clean fclean re