set follow-fork-mode child
set detach-on-fork off
b parse_tokens
run
layout src