CC		= cc
CFLAGS	= -Wall -Werror -Wextra -g

NAME_TESTS	= \
	tokenize

$(NAME_TESTS:%=tests/out/%.out):
	@mkdir -p tests/out
	$(CC) $(CFLAGS) $(@:tests/out/%.out=tests/test_%.c) libft/libft.a -o $@

.PHONY: tests