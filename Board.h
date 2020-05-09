#include <iostream>
#include <cstdlib>
using namespace std;

class Board {
  struct Grid {
    bool ismarked;
    bool flag;
    int index;
  };

  struct Point {
    int x;
    int y;
  };

public:
  // default constructor
  Board() {
    g = new Grid*[1];
    g[0] = new Grid[1];
    mines = new Point[1];
    number_of_flags = 0;
    number_of_mines = 0;
    size = 0;
    explode = false;
  }

  // check if the point has appeared in the array p
  bool isDuplicate(int x, int y, Point * p, int p_len);

  // initialize an empty board with three different levels: 'S' for 10x10, 'M' for 30x30, 'L' for 50x50
  void newBoard(char type);

  // print the current game board
  // if a mine explodes, then print the current board with all mines and "Game Over" on screen
  void printBoard();

  // make a move on the selected grid by the action specified by ch
  void move(int row, int col, char cmd);

  // expand the exposed region to its boundary
  void expand(int row, int col);

  // check if the game is over
  // returns true if explode == true or mines[] is equal to flags[]
  bool win();

  bool lose();

private:
  Grid ** g;
  Point * mines;
  int number_of_mines;
  int number_of_flags;
  int size;
  bool explode;
};
