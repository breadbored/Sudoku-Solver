#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>

char boardValues[9 * 9] = {
  0, 0, 0,  0, 0, 0,  0, 0, 0,
  0, 0, 0,  0, 0, 3,  0, 8, 5,
  0, 0, 1,  0, 2, 0,  0, 0, 0,

  0, 0, 0,  5, 0, 7,  0, 0, 0,
  0, 0, 4,  0, 0, 0,  1, 0, 0,
  0, 9, 0,  0, 0, 0,  0, 0, 0,

  5, 0, 0,  0, 0, 0,  0, 7, 3,
  0, 0, 2,  0, 1, 0,  0, 0, 0,
  0, 0, 0,  0, 4, 0,  0, 0, 9
};

char boardGuess[9 * 9] = {
  0, 0, 0,  0, 0, 0,  0, 0, 0,
  0, 0, 0,  0, 0, 0,  0, 0, 0,
  0, 0, 0,  0, 0, 0,  0, 0, 0,

  0, 0, 0,  0, 0, 0,  0, 0, 0,
  0, 0, 0,  0, 0, 0,  0, 0, 0,
  0, 0, 0,  0, 0, 0,  0, 0, 0,

  0, 0, 0,  0, 0, 0,  0, 0, 0,
  0, 0, 0,  0, 0, 0,  0, 0, 0,
  0, 0, 0,  0, 0, 0,  0, 0, 0
};

std::string draw() {
  std::string board = "";

  // There are 9 number rows, and 10 divider rows,
  // totalling out to 19
  int num_rows = 19;
  int boardPos = 0;

  for (int i = 0; i < num_rows; i++) {
    if (i % 2 == 0) {
      for (int j = 0; j < 9; j++) {
        board += "+";
        if (i * 2 % 3 == 0) {
          board += "===";
        } else {
          board += "---";
        }
      }
      board += "+\n";
    } else {
      for (int j = 0; j < 9; j++) {
        if (j % 3 == 0) {
          board += "ǁ";
        } else {
          board += "|";
        }
        board += " ";
        if (boardGuess[boardPos] > 0) {
          board += "\e[1m"; // Bold text on
          board += std::to_string(boardGuess[boardPos]);
          board += "\e[0m"; // Bold text off
        } else {
          board += " ";
        }
        board += " ";
        boardPos++;
      }
      board += "ǁ\n";
    }
  }

  // const char* cleaned = board.c_str();
  return board;
}

int getNumber(char board[9 * 9], int x, int y) {
  int index = (9 * y) + x;
  if (x >= 0 && x < 9 && y >= 0 && y < 9) {
    return board[index];
  }
  return -1;
}

bool existsInRow(int number, int x, int y) {
  int index = 9 * y;
  for (int i = 0; i < 9; i++) {
    if (number == boardGuess[index + i]) {
      return true;
    }
  }
  return false;
}

bool existsInCol(int number, int x, int y) {
  int index = x;
  for (int i = 0; i < 9; i++) {
    if (number == boardGuess[index + (i * 9)]) {
      return true;
    }
  }
  return false;
}

bool existsInBlock(int number, int x, int y) {
  int blockX = (x / 3) * 3;
  int blockY = (y / 3) * 3;

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (number == boardGuess[(blockX + i) + ((blockY + j) * 9)]) {
        return true;
      }
    }
  }
  
  // for (int i = 0; i < 3; i++) {
  //   for (int j = 0; j < 3; j++) {
  //     if (number == boardGuess[((blockX * 3) + i) + ((blockY * 3) + j)]) {
  //       return true;
  //     }
  //   }
  // }
  return false;
}

bool validNumber(int number, int x, int y) {
  if (getNumber(boardValues, x, y) > 0) {
    return getNumber(boardValues, x, y) == number;
  }
  return !existsInRow(number, x, y) && !existsInCol(number, x, y) && !existsInBlock(number, x, y);
}

void resetToPos(int pos) {
  for (int i = pos; i < 9 * 9; i++) {
    boardGuess[i + 1] = boardValues[i + 1];
  }
}

bool trySolve(int pos) {
  if (pos == ((9 * 9) - 1)) return true;
  int x = pos % 9;
  int y = pos / 9;
  // std::printf("X %s\n", std::to_string(x).c_str());
  // std::printf("Y %s\n", std::to_string(y).c_str());
  for (int i = 0; i < 9; i++) {
    // std:printf("X,Y,i %s, %s, %s\n", std::to_string(x).c_str(), std::to_string(y).c_str(), std::to_string(i).c_str());
    resetToPos(pos);
    if (validNumber(i + 1, x, y)) {
      boardGuess[pos] = i + 1;
      if (trySolve(pos + 1)) {
        // std::string board = draw();
        // std::printf("%s\n", board.c_str());
        return true;
      };
    }
  }
  return false;
}

int main(int argc, char** argv) {

  bool solved = false;
  int guesses = 0;

  // while (!solved) {
    // padding
    std::printf("\n\n");

    // Copy board to guesser
    std::copy(std::begin(boardValues), std::end(boardValues), std::begin(boardGuess));

    // draw
    std::string board = draw();
    std::printf("%s\n", board.c_str());
    std::printf("%s\n", ("Attempt " + std::to_string(guesses)).c_str());

    solved = trySolve(0);

    // draw after solve
    board = draw();
    std::printf("%s\n", board.c_str());
  // }



  std::printf("\n\n");
  return 0;
}
