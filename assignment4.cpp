/*******************************************************************
*** Program:
** Author: Artem Kolpakov
** Date: 3/14/2021
** Description: Based on the entered command line argument, which is the size of the board,
the program displays the empty board with each column numbered across the top.
Then program prompts the first player to select a column. After a column is selected,
the program displays the updated board with the player's piece at the bottom of the selected column.
Player two can then choose a column in which to drop their piece. This behavior continues
(alternating between players) until a winner is determined or until no more pieces
can be dropped into the board (resulting in a tie). At the end program prompts user
if he/she wants to play again, if answer is "1" program runs again.
** Input: 1) a number of rows and a number of columns as a user input
or command line arguments. 2) column where to drop a piece
** Output: empty board, updated board after each move and error/winning messages.
At the end there is a prompt message if user wants to play again.
*******************************************************************/

#include <iostream>
#include <string>

using namespace std;

/*********************************************************************
 * ** Function: print_board
 * ** Description: this function prints empty game board
 * ** Parameters: char** gameBoard, int rows, int columns
 * ** Pre-Conditions: take all the parameters and use them to create a board
 * ** Post-Conditions: create a board and store it at char** gameBoard
 * *********************************************************************/

void print_board(char** gameBoard, int rows, int columns){
    int i, j;
    cout << endl;
    for (i = 0; i < columns; i++){
      if (i<10){
       cout  << "  " << (i + 1) << " ";
      }else{
        cout <<  (i + 1) << "  ";
      }
    }

   cout << endl;
   for (i = 0; i < rows; ++i)
   {
       for (j = 0; j < columns; ++j)
       {
           if (i % 2 == 0 && j % 2 == 0)
           {
               cout << "|\033[30;44m " << gameBoard[i][j]
                   << " " << "\033[30;0m";
           }

           else if (i % 2 == 1 && j % 2 == 1)
           {
               cout << "|\033[30;44m " << gameBoard[i][j]
                   << " " << "\033[30;0m";
           }

           else
               cout << "|\033[30;0m " << gameBoard[i][j] << " ";
       }
       cout << endl;
   }
}

/*********************************************************************
 * ** Function: initialize_board
 * ** Description: initializes char** gameBoard: creates a new char so that there
 * is no seg faults and also sets all cells to empty space
 * ** Parameters: int rows, int columns
 * ** Pre-Conditions: take all the parameters and use them to initialize a board
 * ** Post-Conditions: return 'new' initialized board
 * *********************************************************************/

char** initialize_board(int rows, int cols){

  char **gameBoard = new char*[rows];
  for (int i = 0; i < rows; i++){
     gameBoard[i] = new char [cols];
     for (int j = 0; j< cols; j++){
      gameBoard[i][j] = ' ';
     }
  }
  return gameBoard;
  }

/*********************************************************************
 * ** Function: delete_board
 * ** Description: deletes a gameBoard and frees the memory
 * ** Parameters: char **gameBoard, int rows
 * ** Pre-Conditions: take the num of rows and use it to delete gameBoard
 * ** Post-Conditions: delete gameBoard
 * *********************************************************************/

void delete_board(char **gameBoard, int rows){
  for(int i = 0; i<rows; i++){
    delete [] gameBoard[i];
  }
  delete [] gameBoard;
}

/*********************************************************************
 * ** Function: check_if_int
 * ** Description: checks if provided string has anything except whole numbers
 * * in it.
 * ** Parameters: string prompt
 * ** Pre-Conditions: take a string type parameter
 * ** Post-Conditions: return a bool value that tells if the provided string
 * * has anything except whole numbers in it
 * *********************************************************************/

bool check_if_int(string input){
    int check = 0;

    for (int i = 0; input[i] != '\0'; i++){
if ( input[i] < 48 || input[i] > 57 ) {
    check ++;
}
    }

/*
 * * This for loop searces for anything else exept of integers
 * * using ASCII table values and if such are found
 * * it increments a variable that is needed to get a bool value
 * */

    if (check != 0) {
        return false;
    }
    else {
        return true;
    }
}

/*********************************************************************
 * ** Function: string_to_int
 * ** Description: gets a string and converts it to integer
 * ** Parameters: string prompt
 * ** Pre-Conditions: take a string parameter
 * ** Post-Conditions: returns a "translated" integer num - an integer
 * * corresponding to the one given as a string.
 * *********************************************************************/

int string_to_int(string prompt){
int num = 0;
  for (int a=0; a < prompt[a] != '\0'; a++){
    if( prompt[a] >= 48 && prompt[a] <= 57 ){
      num = (int ( prompt[a] - 48 )) + num * 10;
    /* translates string literal to integer using ASCII table values */
	}
  }
return num;
}

/*********************************************************************
 * ** Function: get_input
 * ** Description: gets a proper input for column from user, checks if it's proper:
 * input can't be more than cols, less than 1, input should be an integer.
 * ** Parameters: char current_player, int cols, char **gameBoard
 * ** Pre-Conditions: take the parameters to check if input is valid
 * ** Post-Conditions: cin valid input and return it -1.
 * *********************************************************************/

int get_input(char current_player, int cols, char **gameBoard){
string input;
if (current_player == 'X'){
    cout << "Player 1's turn (X) : " << endl;
    getline(cin, input);
    }
       else{
           cout << "Player 2's turn (O) : " << endl;
           getline(cin, input);
       }

while ((check_if_int(input) == 0)||(string_to_int(input) > cols) || (string_to_int(input) < 1)){
    cout << "invalid input (whole positive numbers only), please choose a column again: ";
    getline(cin, input);
    }

 while ( check_if_int(input) == 0 || (gameBoard[0][string_to_int(input) -1 ] == 'X'
	|| gameBoard[0][string_to_int(input)-1] == 'O')){
  cout << "The column is full, please choose a column again: ";
    /* here we check if column is full and we keep getting input until it's correct*/
    getline(cin, input);
    }


int int_input = string_to_int(input);
    return int_input-1;
   /* input should be less then one so that we can use it as our column*/
}

/*********************************************************************
 * ** Function: check_if_tie
 * ** Description: this function checks if there is a tie on current gameBoard
 * ** Parameters: char** gameBoard, int cols
 * ** Pre-Conditions: take gameBoard parameter and check if it is full using columns
 * ** Post-Conditions: return bool value true is there is a tie, false otherwise
 * *********************************************************************/

bool check_if_tie(char** gameBoard, int cols){
bool tie = true;
  for (int i = 0; i< cols; i++){
  if (gameBoard[0][i] == ' '){
    tie = false;
    }
  }
/**
 * * since our board is initially filled with empty spaces, here we check the very
 * * top column and the very first row for the whole board and if there is an empty
 * * space it means that the board is not full
 * **/
  return tie;
}

/*********************************************************************
 * ** Function: switch_player
 * ** Description: swaps char info for current player
 * ** Parameters: char current_player
 * ** Pre-Conditions: take the char current_player info and change it
 * ** Post-Conditions: return a new char value for current player
 * *********************************************************************/

char switch_player(char current_player){
  if (current_player == 'X'){
    return 'O';
  }
  else {
    return 'X';
    /* return O if current_player is X, X otherwise */
  }
}

/*********************************************************************
 * ** Function: make_moove
 * ** Description: makes a change on gaming board by showing a moove
 * ** Parameters: int rows, int columns, int specific_column, char current_player,
 * * char** gameBoard
 * ** Pre-Conditions: take all the parameters and use them to make a move
 * ** Post-Conditions: make a change on a board and return a bool value
 * *********************************************************************/

bool make_moove(int rows, int columns, int specific_column, char current_player, char** gameBoard)
{
   /* if the column at specific_column is O or X then we return false */
   if (gameBoard[0][specific_column] == 'O' ||
       gameBoard[0][specific_column] == 'X'){
       return false;
   }

   int i = rows - 1;
   char currentPiece = gameBoard[i][specific_column];
   while (((currentPiece == 'O') || (currentPiece == 'X')) && (i >= 0 )){
       /* here we decrement the row value */
       i--;
       currentPiece = gameBoard[i][specific_column];
   }
   gameBoard[i][specific_column] = current_player;
    /* fill it with current_player char value */
   return true;
}

/*********************************************************************
 * ** Function: get_valid_arg_num
 * ** Description: checks if user entered 3 arguments before starting a program
 * ** Parameters: int argc
 * ** Pre-Conditions: take the num of arguments (argc) and analyze it
 * ** Post-Conditions: return true if there are 3 arguments, false otherwise
 * *********************************************************************/

bool get_valid_arg_num (int argc){
   if (argc < 3){
       cout << "Since you did not enter any arguments or you did not enter enough arguments, we will now ask you for the number of players, rows, and columns at runtime: " << endl;
       return false;
   }
/* we check for 4 because ./main is our first argument */
   if (argc > 3){
       cout << "Since you entered too many arguments, we will now ask you for the number of players, rows, and columns at runtime: " << endl;
       return false;
   }

   if (argc == 3){
       return true;
   }
}

/*********************************************************************
 * ** Function: check_for_vertical_win
 * ** Description: checks if on board there are 4 chips in a row of X or O vertically
 * ** Parameters: int rows, int cols, char current_player, char** gameBoard
 * ** Pre-Conditions: take the parameters and analyze them
 * ** Post-Conditions: return int 4 if there are 4 in a row or 0 otherwise
 * *********************************************************************/

int check_for_vertical_win(int rows, int cols, char current_player, char** gameBoard){
  int count;

for (int i =0; i< cols; i++){
  count = 0;
  char tempPlayer = switch_player(current_player);
  for (int j =0; j< rows; j++){
  if(gameBoard[j][i] == tempPlayer){
    count ++;
/* we increment count if there are any combo connections */
if (count == 4){
  return count;
  }
  }
  else {
    count = 0;
    }
    }
}
return count;
}

/*********************************************************************
 * ** Function: check_for_vertical_win
 * ** Description: checks if on board there are 4 chips in a row of X or O horizontally
 * ** Parameters: int rows, int cols, char current_player, char** gameBoard
 * ** Pre-Conditions: take the parameters and analyze them
 * ** Post-Conditions: return int 4 if there are 4 in a row or 0 otherwise
 * *********************************************************************/

int check_for_horizontal_win(int rows, int cols, char current_player, char** gameBoard){
  int count;
  char tempPlayer = switch_player(current_player);
for (int i =0; i< cols; i++){
  count = 0;
  for (int j =0; j< rows; j++){
  if(gameBoard[i][j] == tempPlayer){
    count ++;
    /* we increment count if there are any combo connections */
if (count == 4){
  return count;
  }
  }
  else {
    count = 0;
    }
    }
}
return count;
}

/*********************************************************************
 * ** Function: check_for_diagonal_win_ltr
 * ** Description: checks if on board there are 4 chips in a row of X or O diagonally
 * * from left bottm to top right
 * ** Parameters: int rows, int cols, char current_player, char** gameBoard
 * ** Pre-Conditions: take the parameters and analyze them
 * ** Post-Conditions: return int 4 if there are 4 in a row or 0 otherwise
 * *********************************************************************/

int check_for_diagonal_win_ltr(int rows, int cols, char current_player, char** gameBoard){
int count;
char tempPlayer = switch_player(current_player);
  for (int i = 0; i< (rows-3); i++){
    count = 0;
  for (int j = 0; j < (cols-3); j++){
    if ( (gameBoard[i + 0][j + 0] == tempPlayer) && (gameBoard[i + 1][j + 1] == tempPlayer)
    && (gameBoard[i + 2][j + 2] == tempPlayer) && (gameBoard[i + 3][j + 3] == tempPlayer)){
      count = 4;
      return count;
    }
    else{
      count=0;
    }
  }
  return count;
}
return count;
}

/*********************************************************************
 * ** Function: check_for_diagonal_win_rtl
 * ** Description: checks if on board there are 4 chips in a row of X or O diagonally
 * * down right
 * ** Parameters: int rows, int cols, char current_player, char** gameBoard
 * ** Pre-Conditions: take the parameters and analyze them
 * ** Post-Conditions: return int 4 if there are 4 in a row or 0 otherwise
 * *********************************************************************/

int check_for_diagonal_win_rtl(int rows, int cols, char current_player, char** gameBoard){
int count;
char tempPlayer = switch_player(current_player);
  for (int i = 3; i< rows; i++){
    count = 0;
  for (int j = 0; j < (cols-3); j++){
    if ( (gameBoard[i][j] == tempPlayer) && (gameBoard[i - 1][j + 1] == tempPlayer)
    && (gameBoard[i-2][j+2] == tempPlayer) && (gameBoard[i-3][j+3] == tempPlayer)){
      count = 4;
      return count;
    }
    else{
      count=0;
    }
  }
}
return count;
}

/*********************************************************************
 * ** Function: int main
 * ** Description: calls all of the above function by looping them and outputs the
 * * updated board after every moove, detects a winned, asks user if they want to run
 * a program again and also contains the error handling for arguments, which means that
 * if the entered arguments are invalid it asks for them during the runtime
 * ** Parameters: int argc, char* argv[]
 * ** Pre-Conditions: take functions, also loop calling them if choice == 1
 * ** Post-Conditions: output their return values: updated board after every moove,
 * winning message, asks user if they want to run a program again, runs a whole loop
 * again if x == 1
 * *********************************************************************/

int main(int argc, char* argv[]){
  char** gameBoard;
  int rows, cols, players_num = 2, moove, choice;
  string player_num_input, rows_input, cols_input;
  char current_player = 'X';
/* here we check if arguments are correct in the case when user enters enough arguments: */
     if (get_valid_arg_num(argc) == 1){
      rows = string_to_int(argv[1]);
          while (rows > 20 || rows < 4){
           cout << "The number of rows must be a positive number less than 20 and greater than 4. " << endl;
           cout << "Please enter the number of rows again: ";
           cin >> rows_input;
           if (check_if_int(rows_input) == 1){
            rows = string_to_int(rows_input);

          }else{
            rows = 0;
          }
           cin.clear();
           cin.ignore();
       }
      cols = string_to_int(argv[2]);
       while (cols > 20 || cols < 4){
           cout << "The number of columns must be a positive number less than 20 and greater than 4. " << endl;
           cout << "Please enter the number of columns again: ";
           cin >> cols_input;
           if (check_if_int(cols_input) == 1){
            cols = string_to_int(cols_input);

          }else{
            cols = 0;
          }
           cin.clear();
           cin.ignore();
       }
   }

/* here we take input at runtime if user enteres not enough/more than 3 arguments: */
   else{
       do {
           cout << "please enter the number of rows (4-20): ";
           cin >> rows_input;
           if (check_if_int(rows_input) == 1){
            rows = string_to_int(rows_input);

          }else{
            rows = 0;
            cout << "the number of rows must be a positive integer! " << endl;
          }
           cin.clear();
           cin.ignore();
       }
       while (rows > 20 || rows <4 );

       do {
           cout << "please enter the number of columns (4-20) ";
           cin >> cols_input;
           if (check_if_int(cols_input) == 1){
           cols = string_to_int(cols_input);

          }else{
            cols = 0;
            cout << "the number of columns must be a positive integer! " << endl;
          }
           cin.clear();
           cin.ignore();
       }
      while (cols > 20 || cols < 4);
   }


int x;
do{
  gameBoard = initialize_board(rows, cols);
/* we loop it while all of those check fucntions are not true */
while (check_if_tie(gameBoard, cols) == 0 &&
(check_for_horizontal_win(rows, cols, current_player, gameBoard) != 4)
&& check_for_vertical_win(rows, cols, current_player, gameBoard) != 4
&& check_for_diagonal_win_ltr(rows, cols, current_player, gameBoard)!= 4
&& check_for_diagonal_win_rtl(rows, cols, current_player, gameBoard)!= 4){
  print_board(gameBoard, rows, cols);
  moove = get_input(current_player, cols, gameBoard);
  make_moove(rows, cols, moove, current_player, gameBoard);
  current_player = switch_player(current_player);

};
print_board(gameBoard, rows, cols);


if (check_if_tie(gameBoard,cols) == 1){
  print_board(gameBoard, rows, cols);
  cout << "Thats a tie ! ;D "<< endl;
}

if (check_for_vertical_win(rows, cols, current_player, gameBoard) == 4) {
  cout << switch_player(current_player) << " wins !"<< endl;
}

if (check_for_horizontal_win(rows, cols, current_player, gameBoard) == 4) {
  cout << switch_player(current_player) << " wins !"<< endl;
}

if (check_for_diagonal_win_ltr(rows, cols, current_player, gameBoard)== 4){
  cout << switch_player(current_player) << " wins !"<< endl;
}

if (check_for_diagonal_win_rtl(rows, cols, current_player, gameBoard)== 4){
  cout << switch_player(current_player) << " wins !"<< endl;
}

  delete_board(gameBoard,rows);

   /* asking user if they want to run the program again */
  cout << "Do you want to play again (1-y, 2-n)? ";
  cin >> x;
  cin.ignore();
}
while (x == 1);

   return 0;
}