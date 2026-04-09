CC		= cc
CFLAGS	= -Wall -Werror -Wextra -g

# TEST_NAMES	= \
# 	tokenize
# TEST_OUTFILES = $(TEST_NAMES:%=tests/out/%.out)

# tests: $(TEST_OUTFILES)

# tests/out/%.out: tests/test_%.c libft/libft.a
# 	@mkdir -p tests/out
# 	$(CC) $(CFLAGS) $< libft/libft.a -o $@

TOKENIZE_TEST_SRCS = \
	$(wildcard src/tokenizer/*.c) \
	tests/test_tokenize.c \
	src/crash.c \
	libft/libft.a

tests:
	@mkdir -p tests/out
	$(CC) $(CFLAGS) $(TOKENIZE_TEST_SRCS) -o tests/out/tokenize.out

.PHONY: tests