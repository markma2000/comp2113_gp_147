# comp2113_gp
Group project for COMP2113. 
Group 147

Group members: 
Ma Tianxing (UID: 3035533965)
Wang Dekang (UID: 3035551395)

This is a text-based game written in C++.

Game name: Minesweeper

Basic rules:
Some mines are located randomly on a checkerboard. Each entry has an index: if it is a mine, the index is -1; if not, its index is equal to the number of mines adjacent to it. The player makes a move by inputting a position (x, y) and a character indicating what operation he/she want to make, 'F' for creating a flag, and 'C' for stepping on it. If the player inputs a position with no mines next to it(index 0), the area containing the current entry encircled by positive indices will be shown on the screen.
The player wins if each mine is marked with a flag, and there are no redundant flags.
The player loses if he/she steps on a mine.


Features/Functions to be implemented:
We plan to write a class called "Board" separate from the main function, which contains the game status and various functions for operation, and a header file "Board.h" containing  the essential information about the Board class, while the main function handles user input (Code requirement 5: Program codes in multiple files). Inside the Board class, we'll use a 2D dynamic array of type Grid as the basic data structure for storing and displaying the game status, and free up the memory when the game is over.

Grid is defined as follows:

struct Grid{
    bool isMarked;
    // represents whether the grid is marked by the player
    int index;
    // determines whether the grid is a mine (if so, then the index is -1), and if not, how many mines are next to it
    bool flag; 
    // represents whether the player thinks this is a mine
};

Public functions of the class Board:
1. Board();
    A default constructor for Board objects
2. void newBoard(char type); (Code requirement 1: Generation of random game sets or events)
    A constructor that generate a board whose size is based on a character input by the player. It randomly generates a certain number of mines on the board, and updates the indices accordingly.
3. void printBoard(); (Code requirement 4: File output)
    A printing function for displaying the game status. It displays the board with all the marked entries, and it will display all the mines if the player steps on a mine.
4. void move(int row, int col, char cmd); (Code requirement 4: File input)
    A function that accepts the position and a character from the player and does the corresponding operation on the board. If the player wants to step on an entry, then if the entry is a mine (index == -1), the function terminates and the player loses the game; if it's safe and has positive index, the entry will be marked; if it has index 0 (in this case, expand() will be called), then the smallest region whose marginal entries all has positive indices will be marked. 
5. expand(int row, int col)
    A recursive function called when the player steps on mine with index 0. It recursively marks the unmarked neighboring entries and terminates either when it reaches an entry with positive index, or when it reaches the boundary of the board.
6. bool win(), bool lose()
    Functions that determine whether the player has won or lost the game. If either returns true, free up the memory occupied by the dynamic arrays.
7. bool isDuplicate(int x, int y, Point * p, int p_len)
    This function checks if the point (x,y) is in the Point array p. It avoids repetition when generating random positions for mines.
    
private variables:
1. Grid ** g; // maintains the marking status, index, and flag for each entry (Code requirement 2: Data structures for storing game status) (Code requirement 3: Dynamic memory management)
2. Point * mines; // stores the position of mines
3. int number_of_mines; // total number of mines
4. int number_of_flags; // maintains the total number of flags created by the player
5. int size; // size of the board
6. bool explode; // initialized to false, set to true if the player steps on a mine
  
 STL used:
<iostream>
<cstdlib>
<ctime>
<iomanip>

Manual guide for players:
The player first specifies what type of board he/she wants to play on. There are 3 sizes: 'S' for 5x5, 'M' for 10x10, 'L' for 15x15.
Then the board with the chosen size will appear on screen. The player then need to repeatedly inputs the position (x, y) and the operation ('F' for flag, 'C' for stepping on it) he/she wants to make, until the game is over. 
The player wins by marking all the mines with flags (no redundant flags), and loses if he/she steps on a mine.
