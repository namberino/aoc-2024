# Advent of Code 2024 solutions

This is my first Advent of Code. This contains solutions to the AOC 2024 puzzles in C++.

# Prerequisite softwares

You will need to install some softwares before using this:

- [Clang](https://clang.llvm.org/)
- [GNU Make](https://www.gnu.org/software/make/)

# Running the solutions

You could go into the individual directory and run it using `make`. There are 4 Makefile rules:

| Rule | Description |
| --- | --- |
| `run` | Compile and run the program with the input file |
| `test` | Compile and run the program with the test file |
| `compile` | Compile the program |
| `clean` | Clean up the executable |

Alternatively, you could use the [run](./run.sh) script. This script allows you to run each solutions without needing to enter the desired directory and manually enter the `make` command.

```
Usage: ./run.sh [day-n] [run | test]
```

# Documentation

Each level solution has some comments on how the solution works.
