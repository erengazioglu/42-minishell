set follow-fork-mode child
set detach-on-fork off
b expand_tokens
run
layout src