# Sudoku-Solver
A sudoku solver to beat my girlfriend

## How to run

### macOS

I set this up with Docker and Docker Compose, because macOS faces library and linking issues when installing build tools via `brew`.

`docker-compose build && docker run sudoku`

### Linux

`g++ -o sudoku main.cpp && ./sudoku`

The current sudoku problem in the `boardValue` variable is the [hardest for a bruteforce method to solve](https://en.wikipedia.org/wiki/Sudoku_solving_algorithms#/media/File:Sudoku_puzzle_hard_for_brute_force.svg). It completes that board in 60 seconds on CPU (20 on GPU via CUDA). Change the `boardValues` variable to solve a different puzzle.


