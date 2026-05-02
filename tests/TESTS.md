# Minishell tests

## Tokenize

`make tests` and run `tests/out/tokenize.out`.

Try stuff like:  
`tests/out/tokenize.out "<" Makefile "|" hey ho "\"hello \$world\"" '$world' "<<" "EOF"`

## Parse

`make tests` and run `tests/out/parse.out` with args.

What to expect with given args:
- `   ` is undefined behavior _(main should skip the first set of newspace characters)_
- `<` (or any other redir character) should return `minishell: syntax error near unexpected token 'newline'`
- `|` followed by however many things should return `minishell: syntax error near unexpected token '|'`
- `> hey` (or any other redir followed by another token) should return an AST with just the redir
- `> >` (or any other redir followed by another redir or pipe) should return `minishell: syntax error near unexpected token <the second character>`.
- `hey     ` should 