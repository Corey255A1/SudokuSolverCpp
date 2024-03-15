# Not just another Sudoku Solver!
An extremely over engineered Sudoku Solver that uses the backtrack algorithm.

![emoji_solve_small_short](https://github.com/Corey255A1/SudokuSolverCpp/assets/3460291/1b3b23b1-afbd-4581-bc39-0404fc901b44)

```
1 5 x x x x x 9 8
9 2 x x 5 x x 4 1
x x 4 x x x 6 x x
x x x 8 x 3 x x x
x 8 x x x x x 3 x
x x x 1 x 4 x x x
x x 2 x x x 9 x x
3 6 x x 9 x x 5 7

-- Solution Found! --
1 5 6 4 3 2 7 9 8
9 2 8 7 5 6 3 4 1
7 3 4 9 8 1 6 2 5
4 1 5 8 6 3 2 7 9
6 8 7 5 2 9 1 3 4
2 9 3 1 7 4 5 8 6
8 7 2 6 4 5 9 1 3
3 6 1 2 9 8 4 5 7
5 4 9 3 1 7 8 6 2
```

It can parse a Sudoku board from a file that is *any* size not just 9x9.  
```
Board Size: 12
x 11 x x 12 5 3 1 8 x 6 x
x x 7 12 6 9 x x x x x 11
x x 1 x x x 8 x x 9 x 5
6 7 x x x x 5 12 x x 3 x
x x 4 3 x 2 6 8 x 5 9 x
x x x x x 10 1 x x x 8 x
x 10 11 x x x 9 2 3 8 7 x
x x 12 x x 4 10 x x 6 5 1
x 8 x x x 3 12 x 10 11 2 x
11 12 x 2 x x x x x 7 x 9
x x 8 1 x x x x 5 x 4 x

-- Solution Found! --
9 11 2 10 12 5 3 1 8 4 6 7
8 5 7 12 6 9 2 4 1 3 10 11
3 4 1 6 11 7 8 10 2 9 12 5
6 7 10 8 9 11 5 12 4 1 3 2
12 1 4 3 7 2 6 8 11 5 9 10
5 2 9 11 4 10 1 3 7 12 8 6
4 10 11 5 1 6 9 2 3 8 7 12
2 3 12 7 8 4 10 11 9 6 5 1
1 8 6 9 5 3 12 7 10 11 2 4
11 12 3 2 10 8 4 5 6 7 1 9
7 9 8 1 2 12 11 6 5 10 4 3
10 6 5 4 3 1 7 9 12 2 11 8
```

It can also read a Sudoku board that is more than just numbers, including **emojis!**.  
```
🤖 🤖 😁 🤖 😆 🤖 🤖 🤖 🤖
🤪 🤖 🤖 😝 😄 😁 😛 🤖 🤖
🤖 🤖 😄 🤖 😃 😀 🤖 😁 🤪
🤖 😄 😆 🤖 🤪 🤖 😁 😜 🤖
🤖 🤪 🤖 🤖 🤖 🤖 🤖 😄 🤖
🤖 😝 😛 🤖 😀 🤖 🤪 😃 🤖
😄 😀 🤖 🤪 😝 🤖 😃 🤖 🤖
🤖 🤖 🤪 😀 😜 😃 🤖 🤖 😄

-- Solution Found! --
😃 😛 😁 😜 😆 🤪 😄 😀 😝
🤪 😜 😀 😝 😄 😁 😛 😆 😃
😝 😆 😄 😛 😃 😀 😜 😁 🤪
😀 😄 😆 😃 🤪 😝 😁 😜 😛
😜 🤪 😃 😆 😁 😛 😝 😄 😀
😁 😝 😛 😄 😀 😜 🤪 😃 😆
😄 😀 😜 🤪 😝 😆 😃 😛 😁
😛 😁 🤪 😀 😜 😃 😆 😝 😄
😆 😃 😝 😁 😛 😄 😀 🤪 😜
```
```
x B x x C 5 3 1 8 x 6 x
x x 7 C 6 9 x x x x x B
x x 1 x x x 8 x x 9 x 5
6 7 x x x x 5 C x x 3 x
x x 4 3 x 2 6 8 x 5 9 x
x x x x x A 1 x x x 8 x
x A B x x x 9 2 3 8 7 x
x x C x x 4 A x x 6 5 1
x 8 x x x 3 C x A B 2 x
B C x 2 x x x x x 7 x 9
x x 8 1 x x x x 5 x 4 x

-- Solution Found! --
9 B 2 A C 5 3 1 8 4 6 7
8 5 7 C 6 9 2 4 1 3 A B
3 4 1 6 B 7 8 A 2 9 C 5
6 7 A 8 9 B 5 C 4 1 3 2
C 1 4 3 7 2 6 8 B 5 9 A
5 2 9 B 4 A 1 3 7 C 8 6
4 A B 5 1 6 9 2 3 8 7 C
2 3 C 7 8 4 A B 9 6 5 1
1 8 6 9 5 3 C 7 A B 2 4
B C 3 2 A 8 4 5 6 7 1 9
7 9 8 1 2 C B 6 5 A 4 3
A 6 5 4 3 1 7 9 C 2 B 8
```
