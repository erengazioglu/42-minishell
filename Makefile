CC		= cc
CFLAGS	= -Wall -Werror -Wextra
DFLAGS	= -g

ifeq ($(shell uname -s),Darwin)
	DFLAGS += -gdwarf-4 -gstrict-dwarf
endif
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
	src/print.c \
	libft/libft.a

tests: libft/libft.a
	@mkdir -p tests/out
	$(CC) $(CFLAGS) $(DFLAGS) $(TOKENIZE_TEST_SRCS) -o tests/out/tokenize.out

libft/libft.a:
	@make -C libft

.PHONY: tests all