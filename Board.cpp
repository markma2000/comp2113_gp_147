#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include "Board.h"
using namespace std;

bool Board::isDuplicate(int x, int y, Point * p, int p_len) {
  for (int i = 0; i < p_len; i++) {
    if (p[i].x == x && p[i].y == y) return true;
  }
  return false;
}

// initialize an empty board with n mines
void Board::newBoard(char type) {
  // generate n random positions
  srand(time(NULL));
  if (type == 'S') {
    size = 5;
    number_of_mines = 5;
  }
  else if (type == 'M') {
    size = 10;
    number_of_mines = 10;
  }
  else if (type == 'L') {
    size = 15;
    number_of_mines = 20;
  }
  else {
    cout << "Invalid type, please enter again: " << endl;
    return;
  }
  g = new Grid*[size];
  for (int i = 0; i < size; i++) {
    g[i] = new Grid[size];
  }
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      g[i][j].ismarked = false;
      g[i][j].flag = false;
      g[i][j].index = 0;
    }
  }

  // randomly generate mines on board
  mines = new Point[number_of_mines];
  int num = 0;
  while (num < number_of_mines) {
    int x = rand() % size;
    int y = rand() % size;
    if (!isDuplicate(x, y, mines, num)) {
      mines[num].x = x;
      mines[num].y = y;
      num++;
    }
  }

  // fill in n mines on the board, update the indices of adjacent grids
  for (int k = 0; k < number_of_mines; k++){
    int r = mines[k].x;
    int c = mines[k].y;
    g[r][c].index = -1;
    if (r > 0 && g[r-1][c].index >= 0) g[r-1][c].index++;
    if (r < size-1 && g[r+1][c].index >= 0) g[r+1][c].index++;
    if (c > 0 && g[r][c-1].index >= 0) g[r][c-1].index++;
    if (c < size-1 && g[r][c+1].index >= 0) g[r][c+1].index++;
    if (r > 0 && c > 0 && g[r-1][c-1].index >= 0) g[r-1][c-1].index++;
    if (r < size-1 && c > 0 && g[r+1][c-1].index >= 0) g[r+1][c-1].index++;
    if (r > 0 && c < size-1 && g[r-1][c+1].index >= 0) g[r-1][c+1].index++;
    if (r < size-1 && c < size-1 && g[r+1][c+1].index >= 0) g[r+1][c+1].index++;
  }
}

// print the current game board
void Board::printBoard() {
  // ruler row
  cout << "Total flags: " << number_of_flags << endl;
  for (int i = 0; i < size+2; i++) {
    if (i < 2) {
      cout << ' ';
    } else {
      cout << (i-1) % 10;
    }
  }
  cout << endl;
  for (int i = 0; i < size+2; i++) {
    if (i < 2) {
      cout << ' ';
    } else {
      cout << '-';
    }
  }
  cout << endl;
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      // ruler column
      if (j == 0) {
        cout << (i+1) % 10 << '|';
      }
      if (g[i][j].flag) {
        cout << '!';
      }
      else {
        if (!g[i][j].ismarked) {
          // if a mine explodes, then print out all of them
          if (g[i][j].index == -1 && explode) {
            cout << '*';
          }
          // print an empty grid
          else cout << 'X';
        }
        else if (g[i][j].index >= 0) {
          cout << g[i][j].index;
        }
      }
      if (j == size-1) {
        cout << '|' << (i+1) % 10;
      }
    }
    cout << endl;
  }
  for (int i = 0; i < size+2; i++) {
    if (i < 2) {
      cout << ' ';
    } else {
      cout << '-';
    }
  }
  cout << endl;
  for (int i = 0; i < size+2; i++) {
    if (i < 2) {
      cout << ' ';
    } else {
      cout << (i-1) % 10;
    }
  }
  cout << endl;
}

// expand the exposed region to its boundary when hits a grid with index 0
void Board::expand(int row, int col){
  g[row][col].ismarked = true;
  // if hits a flag, cancel it, and update number_of_flags
  if (g[row][col].flag) {
    g[row][col].flag = false;
    number_of_flags--;
  }
  // if hits the boundary, stop recursing and return
  if (g[row][col].index > 0) return;
  if (row > 0    && !g[row-1][col].ismarked && g[row-1][col].index >= 0) expand(row-1, col);
  if (row < size-1 && !g[row+1][col].ismarked && g[row+1][col].index >= 0) expand(row+1, col);
  if (col > 0    && !g[row][col-1].ismarked && g[row][col-1].index >= 0) expand(row, col-1);
  if (col < size-1 && !g[row][col+1].ismarked && g[row][col+1].index >= 0) expand(row, col+1);
  if (row > 0    && col > 0    && !g[row-1][col-1].ismarked && g[row-1][col-1].index >= 0) expand(row-1, col-1);
  if (row < size-1 && col > 0    && !g[row+1][col-1].ismarked && g[row+1][col-1].index >= 0) expand(row+1, col-1);
  if (row > 0    && col < size-1 && !g[row-1][col+1].ismarked && g[row-1][col+1].index >= 0) expand(row-1, col+1);
  if (row < size-1 && col < size-1 && !g[row+1][col+1].ismarked && g[row+1][col+1].index >= 0) expand(row+1, col+1);
}

// make a move on the selected grid by the action specified by cmd
void Board::move(int row, int col, char cmd) {
  if (row < 1 || row > size || col < 1 || col > size || (cmd != 'F' && cmd != 'C')) {
    cout << "Invalid command. Please make another move." << endl;
    return;
  }
  int r = row - 1;
  int c = col - 1;
  if (cmd == 'F') {
    if (!g[r][c].flag) {
      g[r][c].flag = true;
      number_of_flags++;
    }
    else {
      g[r][c].flag = false;
      number_of_flags--;
    }
  }
  else if (cmd == 'C') {
    if (g[r][c].index == -1) {
      explode = true;
      return;
    }
    else if (g[r][c].index > 0) {
      g[r][c].ismarked = true;
    }
    else {
      expand(r, c);
    }
  }
}


// the player wins if the flags exactly cover all mines
bool Board::win() {
  int row, col;
  for (int i = 0; i < number_of_mines; i++) {
    row = mines[i].x;
    col = mines[i].y;
    if (!g[row][col].flag) {
      return false;
    }
  }
  if (number_of_flags != number_of_mines) return false;
  for (int i = 0; i < size; i++) {
    delete g[i];
  }
  delete [] mines;
  return true;
}

bool Board::lose() {
  if (explode) {
    for (int i = 0; i < size; i++) {
      delete g[i];
    }
    delete [] mines;
    return true;
  }
  return false;
}
