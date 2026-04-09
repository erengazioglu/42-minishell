# minishell

_This project has been created as part of the 42 curriculum by egaziogl, jalfaiat._

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
- Display a _prompt_ (`<username>@<hostname>:<pwd>`).
- Implement _command history_.
- Search and launch the right executable (PATH var, relative path, absolute path).
- Use at most 1 _global variable_ (to indicate a received signal).
- **Handle single quotes** (`'`) to prevent the shell from interpreting meta-characters.
- **Handle double quotes** (`"`) to prevent the shell from interpreting meta-characters except for `$`.
- **Handle environment variables** ($ followed by a sequence of characters).
- **Handle `$?`** (exit status of last command).
- Implement interruption signals (`ctrl+C, ctrl+D, ctrl+\`).
- Implement _redirections_ (`<<, >>, <, >`).
- Implement _pipes_ (`|`).
- Implement _built-in commands:_
    - `echo -n`,
    - `cd` (relative or absolute path only),
    - `pwd` (no options),
    - `export` (no options),
    - `unset` (no options),
    - `env` (no options/arguments),
    - `exit` (no options).
- **Do not** implement unclosed quotes (where `<newline>` keeps reading input).
- **Do not** implement special characters not explicitly required by the points above.
- **Do not** attempt to fix the `readline` leaks.
- **Limit yourself to the subject description** (anything that isn't asked, isn't required. example: _symlinks, login shell..._).

Bonus requirements:  
- implement `&&` and `||`, with parenthesis for priorities.
- Wildcard `*` working for current directory.

## Instructions

_(no content yet.)_

## Resources

- **man pages** for all the external functions listed above, in the [requirements](#requirements) section.
- other **man pages:**
    - `man dash`
    - `man
