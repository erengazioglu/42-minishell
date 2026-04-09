CC		= cc
CFLAGS	= -Wall -Werror -Wextra -g

TEST_NAMES	= \
	tokenize
TEST_OUTFILES = $(TEST_NAMES:%=tests/out/%.out)

tests: $(TEST_OUTFILES)

tests/out/%.out: tests/test_%.c libft/libft.a
	@mkdir -p tests/out
	$(CC) $(CFLAGS) $< libft/libft.a -o $@

.PHONY: tests