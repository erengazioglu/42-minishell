# minishell | TODO

## REPL loop

- Prompt (waits for user input, reads and returns line).
- Tokenizer (breaks down the input into tokens).
    - Does not validate syntax.
- Parser (uses the tokens to generate an AST).
    - Does validate syntax and return error.
    - Frees the tokens and mallocs an AST.
- Interpreter (uses the AST to run the necessary commands.)
    - Frees the AST.
    - Does it return program info? (e.g. execve this, or run builtin, argc argv...)
- Launcher (handles child processes)
    - Frees program info, creates forks, pipes, redirections...

Implement each part one by one, and test them individually.

## Tokenizer

Examples to try and tokenize:

`pwd` (just a command name)
` pwd   | ls\t` (two piped commands, extra whitespace)
`< infile cat -e | wc -l > outfile` (pipe, command names, options, redirections...)
`echo -n hello | cat -e | wc >> outfile` (redirection, commands, options, args)
`echo $?` (dollar expressions)
`echo -n "hello 42 $USER"    'hello 42 $USER'` (command, option, args, quotations, dollar, whitespace, )

Deferred principles from the examples above:

- A command could be anything, a file name too, and arguments too. So tokenizer shouldn't be able to differentiate between them, and return them as a generic "argument"?
- Whitespace will be ignored (catch also \t etc).
- Unmatched `"` and `'` will be caught by the parser or interpreter later.
- Dollar expressions should be tokenized as a block (e.g. `$USER`).

We should return some sort of list: (example for `echo "hello world $USER" | wc --max-line-length | cat -e > outfile`):
```c
[
    Token(type=TK_WORD, content="echo"),
    Token(type=TK_DQUOTE, content="hello world $USER"),
    Token(type=TK_PIPE, content=""),
    Token(type=TK_WORD, content="wc"),
    Token(type=TK_WORD, content="--max-line-length"),
    Token(type=TK_PIPE, content=""),
    Token(type=TK_WORD, content="cat"),
    Token(type=TK_WORD, content="-e"),
    Token(type=TK_REDIR, content=">"),
    Token(type=TK_WORD, content="outfile")
]
```

Ideas (pseudocode)

```c
while (*line != '\n')
{
    while (ft_strchr(" \t\n", *line))
        line++;
    if (ft_strchr("\"\'", *line))
        line += tokenize_quote(line);
        // makes a single token for "" or '', and returns the length tokenized, 
        // so the line should advance as much.
        // The dollar signs inside will be parsed by the parser 
        // based on whether it's a "" or a ''.
    else if (*line == '$')
        line += tokenize_dollar(line);
        // makes a single token for "$word", and returns its length.
    else if (*line == '\\') 
        line += tokenize_escape(line);
    else
        line += tokenize_arg(line);
}
```