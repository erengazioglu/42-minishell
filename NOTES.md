# Notes

## Readline

To install the readline library on a linux:
- `apt-cache search readline | grep readline` to check what libraries are available
- `sudo apt-get install <library>` to install them.

`libreadline-dev` seem to be the right library to install, but that can change someday, so check!

## Tokenizer

- takes argv&argc, turns them into a linked list of tokens
- does not check validity

## Parser

- takes tokens, turns them into an _Abstract Syntax Tree_ (AST)
- enforces validity of syntax, throwing errors as necessary
- frees tokens as necessary

## Dispatcher

- takes an AST and decides what to do with it
    - if pipe: fork, pipe, redirect, execve
    - if no pipe: redirect, execve
- frees AST and nested tokens


