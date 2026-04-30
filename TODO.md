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

## Parser

The parser should take the tokens and convert them into an AST with multiple binary expressions branching out. From the example earlier:

`echo "hello world $USER" | wc --max-line-length | cat -e > outfile`

It should create something like:

```py
pipe(                               # <-- pipe operator
    "echo hello world user",        # <-- command "operator"
    pipe(
        "wc --max-line-length", 
        "cat -e > outfile"
        )
    )
```

It's a binary tree with processes, so all nodes must have:
- parent node (NULL if root) (necessary??),
- left (left child),
- right (right child),
- operator type (pipe, &&, ||, none (command itself))
- program name (`echo`, `ls`, `/usr/bin/ls`)
- arguments (`hello`, `"hello $USER"`, `'hello $USER'`),
- input redirections (`< infile`, `<< EOF`),
- output redirections (`> outfile`, `>> outfile`),

Dollar sign variables should be expanded at execution time (just before execve call?).

Input and output redirections can exist under EACH node, because this should work:  
`< Makefile cat -e >> outfile | < Makefile wc >> outfile`  
(yes it's pointless to use a pipe here instead of a subshell, but it works, so implement it)

### Actual architecture

- Trees are composed of nodes (pipes, and, or) and leaves (commands). It maps nicely to a union.
- Branches have left and right nodes.
  - Those left and right items can each be nodes or leaves themselves.
- Leaves have argv and redirs.
  - The args are retrieved from tokens, and expanded just before the redirs and execve.
- There can be many of the same redir type! (e.g. `< Makefile cat -e > outfile > out2` will truncate outfile too, but only write to out2). So keep both input and output redirections as one redir list.

Unions are cool: both structs inside the union (`t_astnode` and `t_astleaf`) have the exact same first field (`asttype`), which will be used in determining the behavior of the "execution" as below.

Execution can then be recursive (pseudocode below):
```python
def execute(node):
    if node is pipe:
        execute(pipe.left)
        return execute(pipe.right)
    if node is cmd:
        expand_variables(node)
        redirect()
        return execve()
```

Redirs are tokens that consume the next token and redirect accordingly.  
- `cat < infile hello.txt` will redirect `infile` to `stdin` but then launch `cat hello.txt` with that, thereby `cat`ing both infile and hello.txt.
- `cat -e test_file.txt > outfile test_ptrptr.c > outfile2` this will open both outfiles in succession, so `outfile` will be opened and closed, and `outfile2` will be used. `outfile` will be truncated.
