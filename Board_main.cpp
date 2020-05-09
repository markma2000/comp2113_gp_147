#include <iostream>
#include "Board.h"
using namespace std;


int main() {
  //First show the player the game name and rule.
  cout << "Game name: Minesweeper" << endl;
  cout << "Game Rules: " << endl;
  cout << "Some mines are located randomly on a checkerboard. \nEach entry has an index: if it is a mine, index is -1; if not, its index is equal to the number of mines adjacent to it.\nThe player makes a move by inputting a position (x, y) and a character indicating what operation he/she want to make, \"F\" for creating a flag, and \"C\" for stepping on it. \nIf the player inputs a position with no mines next to it(index 0), the area containing the current entry encircled by positive indices will be shown on the screen." << endl;
  cout << "The player wins if each mine is marked with a flag, and there are no redundant flags." << endl;
  cout << "The player loses if he/she steps on a mine." << endl;
  while (true) {
    //initialize the board;
    char type;
    cout << "Please input the size of the board (\'S\' for 5*5, \'M\' for 10*10, \'L\' for 15*15):" << endl;
    cin >> type;
    while (type != 'S' && type != 'M' && type != 'L') {
      cout << "There is no such type of board. Please enter again: " << endl;
      cin >> type;
    }
    Board *board = new Board();
    board->newBoard(type);
    //finish intialization;
    board->printBoard(); //show the initialized board;
    //let the player input the operation repeatedly until the end of the game;
    while (true) {
      int x, y;
      char operation;
      cout << "Position: ";
      cin >> x >> y;
      cout << "Operation(F/C): ";
      cin >> operation;
      while (operation != 'F' && operation != 'C') {
        cout << "Invalid operation. Please enter again: " << endl;
        cin >> operation;
      }
      cout << endl;
      // change the board;
      board->move(x, y, operation);
      // print the board;
      board->printBoard();
      // examine whether the game is over;
      if (board->win()) {
        cout << "Congratulations! You've sweeped all the mines." << endl;
        break;
      }
      if (board->lose()) {
        cout << "Oops! It seems that you have been blown away...";
        break;
      }
    }
    //ask whether the player want to end or start a new game;
    char next = 'A';
    while (next != 'Y' && next != 'N') {
    cout << "Start a new game? (Y/N): ";
    cin >> next;
    }
    if (next == 'N') break;
  }
  cout << "Thanks for playing!" << endl;
}
