CC = cc
CFLAGS = -Wall -Werror -Wextra -g

NAME = libft.a
SRCS_BASE = \
	ft_atoi.c \
	ft_bzero.c \
	ft_calloc.c \
	ft_get_filename.c \
	ft_isalnum.c \
	ft_isalpha.c \
	ft_isascii.c \
	ft_isdigit.c \
	ft_isprint.c \
	ft_isspace.c \
	ft_itoa.c \
	ft_itoa_base.c \
	ft_itoa_uint.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_memcpy.c \
	ft_memmove.c \
	ft_memset.c \
	ft_minmax.c \
	ft_putchar.c \
	ft_putnbr.c \
	ft_putstr.c \
	ft_satoi.c \
	ft_strunsplit.c \
	ft_split.c \
	ft_str_endswith.c \
	ft_str_equals.c \
	ft_str_isnum.c \
	ft_str_startswith.c \
	ft_strcat.c \
	ft_strchr.c \
	ft_strcpy.c \
	ft_strdup.c \
	ft_strfind.c \
	ft_striteri.c \
	ft_strjoin.c \
	ft_strlcat.c \
	ft_strlcpy.c \
	ft_strlen.c \
	ft_strmapi.c \
	ft_strncmp.c \
	ft_strnstr.c \
	ft_strsjoin.c \
	ft_strtrim.c \
	ft_substr.c \
	ft_tolower.c \
	ft_toupper.c 

SRCS_LIST = \
	ft_lstadd_back.c \
	ft_lstadd_front.c \
	ft_lstclear.c \
	ft_lstdelone.c \
	ft_lstdestroy.c \
	ft_lstfind.c \
	ft_lstget.c \
	ft_lstiter.c \
	ft_lstlast.c \
	ft_lstmap.c \
	ft_lstnew.c \
	ft_lstprint.c \
	ft_lstremove.c \
	ft_lstsize.c

SRCS_PRINTF = \
	ft_printf.c \
	padding_int.c \
	padding_str.c \
	parse.c \
	printf_char.c \
	printf_hex.c \
	printf_int.c \
	printf_percent.c \
	printf_ptr.c \
	printf_str.c \
	printf_uint.c

SRCS_GNL = \
	get_next_line.c

OBJS_BASE	:= $(SRCS_BASE:%.c=obj/base/%.o)
OBJS_GNL	:= $(SRCS_GNL:%.c=obj/gnl/%.o)
OBJS_LIST	:= $(SRCS_LIST:%.c=obj/list/%.o)
OBJS_PRINTF	:= $(SRCS_PRINTF:%.c=obj/printf/%.o)

all: $(NAME) printf list gnl

tests:
	$(CC) $(CFLAGS) tests/test_strfind.c src/base/ft_strlen.c src/extra/ft_strfind.c -o test_strfind.out
	$(CC) $(CFLAGS) tests/test_strchr.c src/base/ft_strlen.c src/base/ft_strchr.c -o test_strchr.out

$(NAME): $(OBJS_BASE)
	@echo $(NAME)
	ar crs $@ $^

gnl: $(OBJS_GNL)
	@echo gnl
	ar crs $(NAME) $^

printf: $(OBJS_PRINTF)
	@echo printf
	ar crs $(NAME) $^

list: $(OBJS_LIST)
	@echo list
	ar crs $(NAME) $^

$(OBJS_BASE): $(SRCS_BASE:%.c=src/base/%.c)
	@mkdir -p obj obj/base
	$(CC) $(CFLAGS) -c $(@:obj/base/%.o=src/base/%.c) -o $@
$(OBJS_GNL): $(SRCS_GNL:%.c=src/gnl/%.c)
	@mkdir -p obj obj/gnl
	$(CC) $(CFLAGS) -c $(@:obj/gnl/%.o=src/gnl/%.c) -o $@
$(OBJS_LIST): $(SRCS_LIST:%.c=src/list/%.c)
	@mkdir -p obj obj/list
	$(CC) $(CFLAGS) -c $(@:obj/list/%.o=src/list/%.c) -o $@
$(OBJS_PRINTF): $(SRCS_PRINTF:%.c=src/printf/%.c)
	@mkdir -p obj obj/printf
	$(CC) $(CFLAGS) -c $(@:obj/printf/%.o=src/printf/%.c) -o $@

fclean: clean
	rm -f $(NAME)
clean:
	rm -rf obj
re: fclean all
.PHONY: all clean fclean re tests
