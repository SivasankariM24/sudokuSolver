# Sudoku Solver

A C++ implementation of a Sudoku puzzle solver using the backtracking algorithm with step-by-step visualization.

## Features

- **Backtracking Algorithm**: Efficiently solves Sudoku puzzles using recursive backtracking
- **Step-by-Step Visualization**: Watch the algorithm work in real-time
- **Input Options**: Enter custom puzzles or use built-in sample puzzle
- **Performance Metrics**: Track solving time and number of steps
- **Input Validation**: Ensures puzzle is valid before solving

## How to Use

### Compilation
```bash
g++ -o sudoku sudoku.cpp
```

### Running
```bash
./sudoku
```

### Menu Options
1. **Enter Custom Puzzle** - Input your own 9x9 Sudoku puzzle
2. **Use Sample Puzzle** - Solve a pre-loaded puzzle
3. **Toggle Step Display** - Turn visualization on/off for faster solving
4. **Exit** - Quit the program

### Input Format
- Use `0` for empty cells
- Enter numbers row by row, space-separated
- Example input for one row: `5 3 0 0 7 0 0 0 0`

## Sample Puzzle

The program includes this sample puzzle:
```
5 3 · · 7 · · · ·
6 · · 1 9 5 · · ·
· 9 8 · · · · 6 ·
8 · · · 6 · · · 3
4 · · 8 · 3 · · 1
7 · · · 2 · · · 6
· 6 · · · · 2 8 ·
· · · 4 1 9 · · 5
· · · · 8 · · 7 9
```

## Algorithm Explanation

The backtracking algorithm works as follows:

1. **Find Empty Cell**: Locate the next empty cell (containing 0)
2. **Try Numbers**: Attempt to place numbers 1-9 in the empty cell
3. **Validate**: Check if the number violates Sudoku rules:
   - No duplicate in the same row
   - No duplicate in the same column
   - No duplicate in the same 3x3 box
4. **Recurse**: If valid, move to the next empty cell
5. **Backtrack**: If no valid number works, remove the current number and try the next one

## Example Output

```
Step 1: Trying 1 at position (1,3)
  ┌───────┬───────┬───────┐
  │ 5 3 1 │ · 7 · │ · · · │ 
  │ 6 · · │ 1 9 5 │ · · · │ 
  │ · 9 8 │ · · · │ · 6 · │ 
  ├───────┼───────┼───────┤
  │ 8 · · │ · 6 · │ · · 3 │ 
  │ 4 · · │ 8 · 3 │ · · 1 │ 
  │ 7 · · │ · 2 · │ · · 6 │ 
  ├───────┼───────┼───────┤
  │ · 6 · │ · · · │ 2 8 · │ 
  │ · · · │ 4 1 9 │ · · 5 │ 
  │ · · · │ · 8 · │ · 7 9 │ 
  └───────┴───────┴───────┘

Backtracking: Removing 1 from position (1,3)
```

## Requirements

- C++ compiler (GCC, Clang, or Visual Studio)
- Standard C++ libraries
- Terminal/Command prompt

## Time Complexity

- **Time**: O(9^(n*n)) in worst case, where n=9
- **Space**: O(n*n) for the recursion stack
- **Practical**: Most valid puzzles solve in milliseconds

## Contributing

Feel free to fork this project and submit improvements such as:
- Alternative solving algorithms (constraint propagation, etc.)
- GUI implementation
- Puzzle generator
- Difficulty analyzer
