_This project has been created as part of the 42 curriculum by egaziogl, jalfaiat._

# minishell

## Description

_(no content yet. To be announced)_

### Requirements

Program execution:
`./minishell` (will take control of the terminal, waiting for user input).

External functions allowed:  
- tty (`isatty, ttyname, ttyslot`),
- error display (`perror, strerror`),
- process management (`fork, wait, waitpid, wait3, wait4, signal, sigemptyset, sigaddset, kill, exit, pipe, execve`),
- I/O (`write, access, open, read, close, dup, dup2, unlink`),
- terminal input & history (`readline, rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay, add_history`),
- terminal control (`tcsetattr, tcgetattr, tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs, ioctl`),
- memory (`malloc, free`)
- file info (`stat, lstat, fstat`)
- directories (`getcwd, chdir, opendir, readdir, closedir`),
- printf.

Mandatory requirements:  
- Display a _prompt_ (e.g. `minishell> `).
- Implement _command history_.
- Search and launch the right executable (PATH var, relative path, absolute path).
- Use at most 1 _global variable_ (to indicate a received signal).
- **Handle single quotes** (`'`) to prevent the shell from interpreting meta-characters.
- **Handle double quotes** (`"`) to prevent the shell from interpreting meta-characters except for `$`.
- Implement _redirections_ (`<<, >>, <, >`).
- Implement _pipes_ (`|`).

- **Do not** implement unclosed quotes (where `<newline>` keeps reading input).
- **Do not** implement special characters not explicitly required by the points above.

Bonus requirements:  
- implement `&&` and `||`, with parenthesis for priorities.
- Wildcard `*` working for current directory.

## Instructions

### Running

1. Run `make` to create the `minishell` executable.
2. Run `./minishell` without arguments, and have fun with it!
3. Hit `CTRL+D` or type `exit` to quit the program.

### Testing

Two config files are provided in the root directory:
- `minishell.supp` (suppression file for `valgrind`)
- `.gdbinit` (init file for `gdb` debugger).

`minishell.supp` is particularly useful for suppressing the leaks originating in the `readline` library, which is out of the project scope.  
To use it in `valgrind`, run it with the `--suppressions=minishell.supp -s` arguments (`-s` will report to you the leaks that have been suppressed this way).

## Resources

- **man pages** for all the external functions listed above, in the [requirements](#requirements) section.
- `bash --posix` for all the tests.
- These two Youtube videos explaining AST:
    - [The Coding Gopher — 99% of Developers Don't Get ASTs](https://www.youtube.com/watch?v=lCrC-qojPpU) (just the first 2 mins),
    - [newline — What Is An Abstract Syntax Tree, With WealthFront Engineer Spencer Miskoviak](https://www.youtube.com/watch?v=wINY109MG10)
- [Robert Nystrom — Crafting Interpreters (ebook).](https://craftinginterpreters.com/a-map-of-the-territory.html) _The web version is free._
- [Posix Shell Grammar](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap02.html).
- This [Minishell Checklist](https://docs.google.com/spreadsheets/d/14SmHNh-gcE0btNqDQE5kMvWpzhDwkvFkdvKzPD2dQDw/edit?usp=sharing) we've worked on.
