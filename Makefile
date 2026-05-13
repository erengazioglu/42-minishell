NAME	= minishell
CC		= cc
CFLAGS	= -Wall -Werror -Wextra
DFLAGS	= -g

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

SRCS = \
	src/globals.c \
	src/crash.c \
	src/print.c \
	src/builtins/ft_cd.c \
	src/builtins/ft_cd_update.c \
	src/builtins/ft_cd_utils.c \
	src/builtins/ft_echo.c \
	src/builtins/ft_env.c \
	src/builtins/ft_exit.c \
	src/builtins/ft_export.c \
	src/builtins/ft_export_utils.c \
	src/builtins/ft_pwd.c \
	src/builtins/ft_unset.c \
	src/builtins/is_builtin.c \
	src/dispatcher/child.c \
	src/dispatcher/dispatch.c \
	src/dispatcher/execute.c \
	src/dispatcher/heredoc.c \
	src/dispatcher/path.c \
	src/dispatcher/redirect.c \
	src/dispatcher/util.c \
	src/expand/expand.c \
	src/expand/expand_string.c \
	src/expand/util.c \
	src/expand/wordsplit.c \
	src/parser/parse.c \
	src/parser/parse_leaf.c \
	src/parser/util.c \
	src/shell/prompt.c \
	src/shell/shell.c \
	src/signals/signals.c \
	src/tokenizer/find.c \
	src/tokenizer/ft_split_quotes.c \
	src/tokenizer/tokenize.c \
	src/tokenizer/tokenize_parts.c \
	src/tokenizer/util.c

MAIN = src/main.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(DFLAGS) $(INCLUDE) -c $< -o $@

$(NAME): libft/libft.a $(OBJS) src/main.o
	$(CC) $(CFLAGS) $(DFLAGS) $(OBJS) src/main.o $(INCLUDE) $(LIBS) -o $@

libft/libft.a:
	@make -C libft

clean:
	rm -f $(OBJS) src/main.o
	@make -C libft clean

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
