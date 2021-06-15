#include "checkers.h"
#include <iostream>
#include <string>

using namespace std;

#define WHITE_SQUARE 0xDB
#define BLACK_SQUARE 0xFF

void Game::newGame(){

   for(int i = 0; i < 8; i++) {
      for(int j = 0; j < 8; j++) {
         board[i][j] = initial_board[i][j];
      }
   }
   //printBoard();
}

bool Game::gameOver(){
   bool game_over = false;
   bool has_B = false;
   bool has_W = false;
   for(int i = 0; i < 8; i++) {
      for(int j = 0; j < 8; j++) {
         if(board[i][j] == 'B'){
            has_B = true;
         }
         if(board[i][j] == 'W'){
            has_W = true;
         }
      }
   }
   if(has_B == false || has_W == false) {
      return true;
   } else return false;
}

void Game::printBoard(){
   cout << "  ";
   for(int k = 0; k < 8; k++) {
      cout << '|' << k << '|';
   } cout << "\n";
   for(int i = 0; i < 8; i++) {
      cout  << i << " ";
      for(int j = 0; j < 8; j++) {
         cout << '|' << board[i][j] << '|';
      } cout << "\n";
   } cout << "\n";
}

char Game::getColorPieceAtPosition(int row, int column){
   return board[row][column];
}

// enum Checkers::Direction Game::getDirectionOfMovingPiece(){
//    return Direction;
// }

void Game::movePiece(Position present, Position future){
   // First, get the piece that needs to be moved
   char curr_piece = getPieceAtPosition(present);
   

}

void Game::movePiece(int curr_row, int curr_column, int row, int column) {
   char curr_piece = board[curr_row][curr_column];
   char future_spot = board[row][column];

   if(future_spot != 0x20) { //There is a piece where current piece is trying to move
      if(future_spot != curr_piece) { //If where you are trying to move has the other color piece there, jump it
         if(board[row][column] == 'B') numberOfJumpedB++;
         if(board[row][column] == 'W') numberOfJumpedW++;
         board[row][column] = 0x20; //Clear the piece you jumped

         //Which direction you trying to move?
         if(row < curr_row && column < curr_column) {
            // Going up_left
            row--;
            column--;
         } else if(row < curr_row && column > curr_column) {
            // Going up_left
            row--;
            column++;
         } else if(row > curr_row && column < curr_column) {
            // Going up_left
            row++;
            column--;
         } else if(row > curr_row && column > curr_column) {
            // Going up_left
            row++;
            column++;
         }
         board[row][column] = curr_piece;
         board[curr_row][curr_column] = 0x20;
      } else { //If where you are trying to go is your color, can't do that
         cout << "Can not move to a space already occupied by your color\n";
      }
   } else {
      board[row][column] = curr_piece;
      board[curr_row][curr_column] = 0x20;
   }
   cout << "---------------------------------------" << endl;
   cout << "Number of Jumped B: " << numberOfJumpedB << endl;
   cout << "Number of Jumped W: " << numberOfJumpedW << endl;
}

Game::Position Game::getCoordinates(string spot){
   char row = spot[0];
   int column = spot[1];
   Position position;

   switch(row) {
      case 'A':
         position.row = 0;
         break;
      case 'B':
         position.row = 1;
         break;
      case 'C':
         position.row = 2;
         break;
      case 'D':
         position.row = 3;
         break;
      case 'E':
         position.row = 4;
         break;
      case 'F':
         position.row = 5;
         break;
      case 'G':
         position.row = 6;
         break;
      case 'H':
         position.row = 7;
         break;
      default:
         cout << "Invalid column choice." << endl;
   }
   position.column = column;
   return position;
}

void Game::turn(){
   int curr_row, curr_column, row, column;
   string curr_piece, future_spot;
   Position curr_piece_positiion;
   Position future_spot_position;

   cout << "What piece do you want to move? -> ";
   cin >> curr_piece;
   cout << "Where do you want to move? -> ";
   cin >> future_spot;
   cout << endl;

   Position curr_piece_position = getCoordinates(curr_piece);
   Position future_spot_position = getCoordinates(future_spot);


}

char Game::getPieceAtPosition(Position position){
   return board[position.row][position.column];
}

void Board::printLine(int iLine, int iColor1, int iColor2, Game& game){
   // Example (for CELL = 6):

   //  [6-char]
   //  |______| subline 1
   //  |___Q__| subline 2
   //  |______| subline 3

   // Define the CELL variable here. 
   // It represents how many horizontal characters will form one square
   // The number of vertical characters will be CELL/2
   // You can change it to alter the size of the board (an odd number will make the squares look rectangular)
   int CELL = 6;

   // Since the width of the characters BLACK and WHITE is half of the height,
   // we need to use two characters in a row.
   // So if we have CELL characters, we must have CELL/2 sublines
   for (int subLine = 0; subLine < CELL/2; subLine++) {
      // A sub-line is consisted of 8 cells, but we can group it
      // in 4 iPairs of black&white
      for (int iPair = 0; iPair < 4; iPair++) {
         // First cell of the pair
         for (int subColumn = 0; subColumn < CELL; subColumn++) {
            //  cout << char(iColor1);
            // The piece should be in the "middle" of the cell
            // For 3 sub-lines, in sub-line 1
            // For 6 sub-columns, sub-column 3
            if (subLine == 1 && subColumn == 3) {
               cout << char(game.getColorPieceAtPosition(iLine, iPair*2) != 0x20 ? game.getColorPieceAtPosition(iLine, iPair*2) : iColor1);
            // cout << "B";
            }
            else {
               cout << char(iColor1);
            }
         }

         // Second cell of the pair
         for (int subColumn = 0; subColumn < CELL; subColumn++) {
            // The piece should be in the "middle" of the cell
            // For 3 sub-lines, in sub-line 1
            // For 6 sub-columns, sub-column 3
            if ( subLine == 1 && subColumn == 3) {
               cout << char(game.getColorPieceAtPosition(iLine, iPair*2+1) != 0x20 ? game.getColorPieceAtPosition(iLine, iPair*2+1) : iColor2);
            // cout << "R";
            }
            else {
               cout << char(iColor2);
            }
         }
      }

      // Write the number of the line on the right
      if ( 1 == subLine ) {
         cout << "   " << iLine+1;
      }
      cout << "\n";
   }
}

void Board::printBoard(Game& game){
    cout << "   A     B     C     D     E     F     G     H\n\n";

    for(int iLine = 7; iLine >= 0; iLine--) {
        if (iLine%2 == 0) { //iLine is even
            //Line starting with black
            printLine(iLine, BLACK_SQUARE, WHITE_SQUARE, game);
        } else {
            // Line starting with white
            printLine(iLine, WHITE_SQUARE, BLACK_SQUARE, game);
        }
    }
}




