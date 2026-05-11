Exit status + parser issues (minishell tester)

High impact causes observed

1) execute_relative() does not exit on failure
   - src/dispatcher/dispatch.c: execute_relative() prints "command not found" but
     never exits with 127
   - This contributes to PATH tests failing (expect 127/126 vs 1)

2) Syntax errors return 1 instead of 2
   - parse_tokens() and check_unexpected_token() print errors but do not set
     last_exit_status to 2
   - main.c: get_input() error prints syntax error, but last_exit_status is not
     updated

3) wait_children() uses uninitialized exit_code
   - src/dispatcher/dispatch.c: exit_code is not initialized before wait loop
   - Can yield random exit status when last pid is not caught

4) Expansion/quoting behavior differs from bash
   - src/dispatcher/expand.c: no backslash handling, no bash-like field splitting
   - Tests in cmds/mand/0_compare_parsing.sh and 1_variables.sh likely fail
     because of $?, $"HOME", backslashes, and quote-merge cases

Suggested focus order

1) Fix exit status propagation and known exit codes (127/126/2)
2) Fix wait_children() deterministic return value
3) Re-check failing groups: syntax (m s), path (m path), variables (m v)
4) Then refine expansion/quoting behavior

Files to inspect

- src/dispatcher/dispatch.c
- src/parser/parse.c
- src/parser/parse_leaf.c
- src/dispatcher/expand.c
- src/main.c
