# Maze Solver
A c++ program to solve simple maze using DFS algorithm. The maze is represented as a 2D array of characters, where S represents the start, E represents the end, # represents walls, and spaces represent empty cells. The program uses the SFML library to visualize the maze and the solution.

## Usage

Compile the program using the following command:

```bash
g++ -o maze_solver maze_solver.cpp -lsfml-graphics -lsfml-window -lsfml-system
```

## Maze Representation

- 'S': Start point
- 'E': End point
- '#': Wall
- ' ': Empty space
- 'V': Visited space
- 'X': Path taken
