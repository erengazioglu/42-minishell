# push_swap

[Français](README.fr.md)

*Reading a line, one buffer at a time... wait, wrong project.*

---

## Description

`minishell` is a

**What I learned:**

**The challenge:**

---

## How to use

### Compile

```bash
make
```

### Run

```bash

```

### What it outputs

A series of operations like:
```

```

These operations, when applied to the original stack, will sort it.

---

## The Builtins

| Operation | What it does |
|-----------|-------------|
| `sa` | Swap first 2 elements of stack A |
| `sb` | Swap first 2 elements of stack B |
| `pa` | Push top of B onto A |
| `pb` | Push top of A onto B |
| `ra` | Rotate A up (first element becomes last) |
| `rb` | Rotate B up |
| `rr` | Rotate both A and B at the same time |
| `rra` | Reverse rotate A (last element becomes first) |
| `rrb` | Reverse rotate B |
| `rrr` | Reverse rotate both at the same time |

---

## My approach

### For small stacks (2-3 numbers)

Just hardcoded the optimal moves. Not worth overthinking.

- 2 numbers: Swap if needed. Done.
- 3 numbers: Max 2 operations. Easy.

### For big stacks (100-500 numbers): The Turk Algorithm

This is where it gets interesting.

**Step 1: Give every number a rank**

Instead of comparing values like `42 < 100`, I assign ranks (0, 1, 2...) based on their sorted position. Way faster.

**Step 2: Push almost everything to stack B**

Leave 3 numbers in A, push the rest to B. Now A is easy to sort.

**Step 3: Sort the 3 numbers in A**

Hardcoded optimal solution.

**Step 4: Bring everything back from B to A (the smart way)**

This is where the magic happens. For every number in B:

1. Find its **target** in A (where it should go)
2. Calculate the **cost** to move it (how many rotations needed)
3. Pick the **cheapest** one and move it first

**The optimization:** When both the number in B and its target in A are on the same side (both above or both below the median), I can rotate both stacks at the same time using `rr` or `rrr`. This saves a ton of operations.

**Step 5: Final rotation**

Rotate A until the smallest number is at the top. Done.

---

## Why this works

The key insight: **not all moves cost the same.**

If I need to rotate A 5 times and B 3 times, and they're both rotating in the same direction, I can do 3 `rr` operations (simultaneous) + 2 `ra` operations = **5 total ops instead of 8**.

This small optimization dropped my average from ~5,700 operations to ~5,160 for 500 numbers.

---

## My data structure

I used a doubly-linked list for each stack:

```c
typedef struct s_stack
{
    int             value;          // The actual number
    int             rank;           // Its sorted position
    int             index;          // Current position in stack
    int             push_cost;      // Cost to move this node
    bool            above_median;   // Is it in the top half?
    bool            cheapest;       // Is this the cheapest to move?
    struct s_stack  *target_node;   // Where it should go in the other stack
    struct s_stack  *next;
    struct s_stack  *prev;
}                   t_stack;
```

Why doubly-linked? So I can rotate in both directions efficiently.

---

## Performance

| Test | My result | Target | Grade |
|------|-----------|--------|-------|
| 3 numbers | ≤ 3 ops | ≤ 3 | ✅ |
| 5 numbers | ≤ 12 ops | ≤ 12 | ✅ |
| 100 numbers | ~608 ops | < 700 | ✅ |
| 500 numbers | ~5,160 ops | < 5,500 | ✅ |

**Final grade: 30/30**

---

## Error handling

The program prints `Error` and exits if:

- Input has duplicates (`1 2 2 3`)
- Input has non-numeric values (`1 two 3`)
- Numbers overflow `INT_MIN` or `INT_MAX`
- Empty strings or invalid format

If the stack is already sorted, it just exits (no output needed).

---

## What went wrong (and how I fixed it)

### Attempt 1: Radix sort

My first implementation used radix sort. Clean, simple, easy to understand.

**Problem:** ~6,700 operations for 500 numbers. Failed the test.

I had to scrap it and learn a better algorithm.

### Attempt 2: Turk algorithm (first version)

Implemented the Turk algorithm from a video tutorial.

**Problem:** Still getting ~5,700 operations. Barely passing sometimes, failing others.

### Attempt 3: Cost optimization

I realized I was calculating costs wrong. I was **adding** the rotation costs for both stacks, even when they could rotate simultaneously.

**The fix:**
```c
// Before (wrong)
cost = cost_a + cost_b;  // Always adding

// After (correct)
if (same_side)
    cost = max(cost_a, cost_b);  // Can rotate together
else
    cost = cost_a + cost_b;  // Must rotate separately
```

This **one change** dropped me to ~5,160 operations. Consistent 100% pass rate.

---

## Project structure

```
.
├── Makefile
├── README.md
├── README.fr.md
├── includes/
│   └── push_swap.h
├── srcs/
│   ├── main.c
│   ├── stack_utils.c
│   ├── validation.c
│   ├── stack_init.c
│   ├── parsing/
│   │   ├── parser.c
│   │   └── parse_helpers.c
│   ├── sort/
│   │   ├── sort_small.c
│   │   ├── sort_utils.c
│   │   ├── turk_init.c
│   │   ├── turk_cost.c
│   │   ├── turk_move.c
│   │   └── turk_sort.c
│   └── operations/
│       ├── push.c
│       ├── swap.c
│       ├── rotate.c
│       └── rev_rotate.c
├── libft/
└── ft_printf/
```

Originally everything was in the root directory with names like `turk.c`, `turk2.c`, `turk3.c`. Cleaned it up at the end.

---

## Testing

```bash
# Basic tests
./push_swap 3 2 1
./push_swap 5 4 3 2 1

# Error cases
./push_swap 1 2 1          # Duplicates
./push_swap 2147483648     # Overflow
./push_swap "a b c"        # Non-numeric

# Performance (requires push_swap_tester)
./complexity 100 100 700 ./push_swap
./complexity 500 20 5500 ./push_swap

# Memory leaks
valgrind --leak-check=full ./push_swap 5 4 3 2 1
```

---

## Resources I used

**Tutorials:**
- Watched multiple YouTube videos on push_swap approaches
- Read through example implementations (did not copy, just understood the logic)

**Documentation:**
- `man malloc`, `man free`, `man write`
- Big O notation and algorithm complexity theory

**Tools:**
- Used `push_swap_tester` to benchmark performance
- Used `valgrind` to catch memory leaks
- Used NotebookLM to analyze a video transcript and extract optimization details

**AI usage:**
- Started with radix sort (simple but slow)
- AI explained why it was not good enough for 500 elements
- Learned about the Turk algorithm and greedy heuristics
- Got help debugging the cost calculation (the key optimization)
- Fixed norminette issues (line count, variable count)
- Reorganized the project structure for clarity

I wrote every line of code myself. AI was my code reviewer and mentor, not my solution generator.

---

## What I actually learned

1. **Algorithm choice matters more than I thought.** Radix was elegant but too slow. Turk was messier but way faster.
2. **Small optimizations compound.** The `rr` / `rrr` optimization saved ~500 operations across 500 numbers. That is the difference between passing and failing.
3. **Greedy works surprisingly well.** Always picking the "cheapest" move is not optimal, but it is close enough and way faster than calculating the perfect solution.
4. **Code organization is worth it.** Refactoring from a flat structure to organized folders made debugging way easier.
5. **Testing reveals everything.** Edge cases I never thought of (empty strings, overflow, duplicates) all showed up during testing.

---

**This project taught me to think about efficiency, not just correctness.**
