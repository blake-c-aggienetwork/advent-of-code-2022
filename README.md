# Advent of Code 2022

Here are my solutions for Advent of Code 2022. I have written them in C++ to become more proficient in the language and compete in a private leaderboard from an internet community.

https://adventofcode.com/

## Stats

|       | Part 1   |      |       | Part 2   |      |       |
|-------|----------|------|-------|----------|------|-------|
|       | Time     | Rank | Score | Time     | Rank | Score |
| Day 1 | 00:10:42 | 5581 | 0     | 00:19:53 | 6730 | 0     |
| Day 2 | 00:18:49 | 7702 | 0     | 00:25:09 | 6511 |  0    | 

## Notes on My Approach to each problem

#### Day 1
- Don't need to use a max heap-- guess I panicked and immediately used it
- Should've have realized C++ does indeed have a sort function
- Not a very optimal approach
- Optimal approach is iterating through the file and inserting each calorie count into a max heap of size 3

#### Day 2 
- This day should've been faster, many typos
- using a switch case if probably better, but am not familiar in c++

## Run Locally

Clone the project

```bash
  git clone https://github.com/blake-c-aggienetwork/adventOfCode2022
```

Navigate to the desired puzzle 

```bash
  cd adventOfCode2022/01
```

Compile the code-- I am using clang for this, update the $(CC) in the makefile to change

```bash
  make
```

Run the executable

```bash
  ./main.out
```

