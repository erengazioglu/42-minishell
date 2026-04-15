# libft

_This project has been created as part of the 42 curriculum by egaziogl._

## Description

`libft` is the first assignment in the common core of 42 curriculum, consisting of a C library implementing useful functions, for future use in 42 projects.

The initial assignment prescribes the implementation of many fundamental functions, consisting of 3 parts:

1. Libc functions:
    - isalpha, isdigit, isalnum, isascii, isprint;
    - bzero, memset, memcpy, memmove, memcmp, memchr;
    - strlen, strchr, strrchr, strncmp, strnstr, strlcpy, strlcat;
    - atoi.
2. Additional functions:
    - ft_substr,
    - ft_strjoin,
    - ft_strtrim,
    - ft_split,
    - ft_itoa,
    - ft_strmapi,
    - ft_striteri,
    - ft_putchar_fd,
    - ft_putstr_fd,
    - ft_putendl_fd,
    - ft_putnbr_fd.
3. Linked list:
    - ft_lstnew,
    - ft_lstadd_front,
    - ft_lstadd_back,
    - ft_lstsize,
    - ft_lstlast,
    - ft_lstdelone,
    - ft_lstclear,
    - ft_lstiter,
    - ft_lstmap.

The library has evolved significantly since. The biggest changes:
- new helper functions that were creating during other projects were added,
- certain functions have been reworked for additional functionality,
- functions have been regrouped into meaningful categories (base, gnl, list...) and their headers clearly separated, so that they can be picked individually,
- every single function has been documented with _doxygen-style docstrings,_ which in combination with the Vscode C/C++ extensions enabled, generate helpful tooltips.

## Instructions

- Run `make` to generate the `libft.a` file with all the functions (alternatively, you can specify individual categories to bundle into `libft.a` as defined in the Makefile).
- To use libft in your code, either `#include "libft/include/libft.h"` or the individual parts you need from it (e.g. `#include "libft/include/libft_printf.h`).
- When compiling your own project, include `libft.a` in your compilation (e.g. `cc main.c libft.a`).

## Resources

- `man` pages for every standard function used.
- The "Resources" section from every other 42 project repository contributed to the creation of the helper functions needed for the respective projects.
- Back-and-forth with 42 peers, sharing tips and favorite ways of writing code in C.
