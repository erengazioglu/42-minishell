# Minishell Builtins - The Baby Guide 🍼

This document explains what every builtin in our Minishell does in the simplest possible terms.

## The 3 Files Built So Far

### 1. `echo.c` (The Parrot) 🦜
- **What it does:** It literally just repeats whatever you say back to you.
- **Baby explanation:** If you say "hello", it says "hello" back. If you give it a special `-n` flag, it promises not to hit the "Enter" key (newline) after it speaks.

### 2. `env.c` (The Backpack Checker) 🎒
- **What it does:** It prints out all the hidden system variables (the environment) that are currently active and have a value.
- **Baby explanation:** Imagine your shell is wearing a backpack full of labeled items (like `USER=joaolopes`). When you run `env`, the shell just dumps out the backpack and reads everything inside it out loud, line by line.

### 3. `exit.c` (The Light Switch) 💡
- **What it does:** It safely shuts down your shell, cleans up the mess, and tells the computer if the program succeeded or failed.
- **Baby explanation:** It turns off the lights and goes to sleep. But before it sleeps, it checks to make sure you didn’t give it a weird goodbye message (like "letters" instead of a "number"), and cleans its room (frees memory!).'

### 6. `export.c` (The Label Maker) 🏷️
- **What it does:** Adds or updates variables in your environment list (your backpack).
- **Baby explanation:** It lets you stick a new label onto an item and throw it into the backpack. If you type `export COLOR=blue`, you just told the shell to remember your favorite color forever. It also shows you the whole backpack in *alphabetical order* if you run it with no arguments.

### 7. `unset.c` (The Eraser) 🧽
- **What it does:** Removes variables from your environment list entirely.
- **Baby explanation:** If you don't want the shell to remember your favorite color anymore, you type `unset COLOR` and it permanently deletes it from the backpack.

### 4. `pwd.c` (The Map) 🗺️
- **What it does:** Prints the "Print Working Directory" (your current folder path).
- **Baby explanation:** It’s like the "You Are Here" red dot on a mall map. It tells you exactly which folder your terminal is currently sitting inside.

---

## The 4 Files To Build Next


### 5. `cd.c` (The Teleporter) 🚀
- **What it does:** Changes Directory. It updates your current path to a new location.
- **Baby explanation:** It teleports you from your current folder into a new folder. If you say `cd desktop`, it beams you over to the desktop!
