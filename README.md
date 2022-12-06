# Advent of Code 2022

Here are my solutions for Advent of Code 2022. I have written them in C++ to become more proficient in the language and compete in a private leaderboard from an internet community.

The code itself is not particularly good since I have not written in C++ for a long time and the goal is to solve the question as fast as possible. 

https://adventofcode.com/

## Global Ranking by Time and Stats

|       | Part 1   |      |       | Part 2   |      |       |
|-------|----------|------|-------|----------|------|-------|
|       | Time     | Rank | Score | Time     | Rank | Score |
| Day 1 | 00:10:42 | 5581 | 0     | 00:19:53 | 6730 | 0     |
| Day 2 | 00:18:49 | 7702 | 0     | 00:25:09 | 6511 |  0    | 
| Day 3 | 00:24:15 | 8597 | 0     | 00:36:38 | 8156 |  0    |
| Day 4 | 00:32:13 | 12036|     0 | 00:46:51 | 12773|      0|
| Day 5 |  00:34:35| 6628 |    0  | 00:38:33 |  6066|      0|
| Day 6 | 00:44:13 | 16782|      0| 00:47:10 | 16107|      0|

## Notes on My Approach to each problem

#### Day 1
- Don't need to use a max heap-- guess I panicked and immediately used it
- Should've have realized C++ does indeed have a sort function
- Not a very optimal approach
- Optimal approach is iterating through the file and inserting each calorie count into a max heap of size 3

#### Day 2 
- This day should've been faster, many typos
- using a switch case if probably better, but am not familiar in c++

#### Day 3
- Took a lot more time today
- Gets a warning a the comparison
- Probably could use an array of size 52 instead of map for keeping track of characters
- That would save on memory since index will equal priority
- I don't need to use a frequency map, just a bool to keep track of seen chars

#### Day 4
- Took a long time to figure out how string splitting works in C++
- Using a set for Part2 intersection checking is unnecessary  
- I have since looked up better approaches for input reading, sscanf() really simplifies this

#### Day 5
- I gave up on parsing this immediately
- Actual problem not too hard once the input is parsed
- I went up in placement a lot globally
- Went back and figured out how to parse the input nicely on day 6

#### Day 6
- Recognized this as a two pointers sliding window problem
- Still took too much time on this


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

