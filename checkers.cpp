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

char Game::getWinner(){
   if(numberOfJumpedB > numberOfJumpedW){
      cout << "White pieces won!\n";
      return 'W';
   } else if(numberOfJumpedW > numberOfJumpedB){
      cout << "Black pieces won!\n";
      return 'B';
   } else if(numberOfJumpedB == numberOfJumpedW){
      cout << "Draw\n";
      return 'D';
   } else {
      cout << "ERROR in getWinner()\n";
      return 'E';
   }
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

bool Game::movePiece(Position present, Position future){
   // First, get the piece that needs to be moved
   char curr_piece = getPieceAtPosition(present);
   // Next, get future_spot of moving piece
   char future_spot = getPieceAtPosition(future);
   Position temp = future;
   bool moveSuccess = false;
   bool whiteSpace = false;
   
   //For loop here to check if future position is a white space
   for(int i = 0; i < 32; i++){
      if (future.row == white_spaces[i].row && future.column == white_spaces[i].column){
         whiteSpace = true;
      }
      
   }
   
   if(future_spot != 0x20) { //There is a piece where current piece is trying to move
      if(future_spot != curr_piece) { //If where you are trying to move has the other color piece there, jump it
         if(future_spot == 'B') numberOfJumpedB++;
         if(future_spot == 'W') numberOfJumpedW++;
         // setPieceAtPosition(future, 0x20); //Clear the piece you jumped

         //Which direction you trying to move?
         if(future.row < present.row && future.column < present.column) {
            // Going 
            // cout << "Here: row-- and column--\n";
            //For B -> down_left
            future.row--;
            future.column--;
         } else if(future.row < present.row && future.column > present.column) {
            // Going 
            // cout << "Here: row-- and column++\n";
            //For B -> down_right
            future.row--;
            future.column++;
         } else if(future.row > present.row && future.column < present.column) {
            // Going 
            // cout << "Here: row++ and column--\n";
            //For W -> up_left
            future.row++;
            future.column--;
         } else if(future.row > present.row && future.column > present.column) {
            // Going 
            // cout << "Here: row++ and column++\n";
            //For W -> up_right
            future.row++;
            future.column++;
         }

         if(getPieceAtPosition(future) == 0x20) {
            // If the spot to jump to is blank, then jump
            setPieceAtPosition(temp, 0x20); //Clear the piece you jumped
            setPieceAtPosition(future, curr_piece);
            setPieceAtPosition(present, 0x20);
            newSpot = future;
            jumpedAPiece = true;
            moveSuccess = true;
         } else {
            // Can't jump to a spot that is occupied
            cout << "Cannot jump to an occupied space.\n";
         }
      } else {
         //If where you are trying to go is your color, can't do that
         cout << "Can not move to a space already occupied by your color.\n";
      }
   } else if(whiteSpace){
      // If the spot you want to move to is a white space, try again
      cout << "Can not move to a white space.\n";
   } else { //There isn't a piece where current piece is trying to move
      setPieceAtPosition(future, curr_piece);
      setPieceAtPosition(present, 0x20);
      newSpot = future;
      jumpedAPiece = false;
      moveSuccess = true;  //piece was moved
   }
   previousPiece = newSpot;
   // cout << "---------------------------------------" << endl;
   // cout << "Number of Jumped B: " << numberOfJumpedB << endl;
   // cout << "Number of Jumped W: " << numberOfJumpedW << endl;
   if(!moveSuccess) cout << "Move unsuccessful, please try again." << endl;
   return moveSuccess;
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
   char column = spot[1];
   // cout << spot[1];
   Position position;

   switch(row) {
      case 'A':
      case 'a':
         position.column = 0;
         break;
      case 'B':
      case 'b':
         position.column = 1;
         break;
      case 'C':
      case 'c':
         position.column = 2;
         break;
      case 'D':
      case 'd':
         position.column = 3;
         break;
      case 'E':
      case 'e':
         position.column = 4;
         break;
      case 'F':
      case 'f':
         position.column = 5;
         break;
      case 'G':
      case 'g':
         position.column = 6;
         break;
      case 'H':
      case 'h':
         position.column = 7;
         break;
      default:
         cout << "Invalid column choice." << endl;
   }

   switch(column){
      case '1':
         position.row = 0;
         break;
      case '2':
         position.row = 1;
         break;
      case '3':
         position.row = 2;
         break;
      case '4':
         position.row = 3;
         break;
      case '5':
         position.row = 4;
         break;
      case '6':
         position.row = 5;
         break;
      case '7':
         position.row = 6;
         break;
      case '8':
         position.row = 7;
         break;
      default:
         cout << "Invalid row choice." << endl;
   }
   // cout << "column: " << column << endl;
   
   return position;
}

bool Game::turn(){
   int curr_row, curr_column, row, column;
   string curr_piece, future_spot;
   Position curr_piece_position;
   Position future_spot_position;

   cout << "What piece do you want to move? -> ";
   cin >> curr_piece;
   cout << "Where do you want to move? -> ";
   cin >> future_spot;
   cout << endl;

   curr_piece_position = getCoordinates(curr_piece);
   future_spot_position = getCoordinates(future_spot);
   // cout << curr_piece_position.row << ", " << curr_piece_position.column << endl;
   // cout << future_spot_position.row << ", " << future_spot_position.column << endl;

   return movePiece(curr_piece_position, future_spot_position);
   // while(move != true){
   //    move = movePiece(curr_piece_position, future_spot_position);
   // }

   // cout << "newSpot: _" << getPieceAtPosition(newSpot) << "_" << endl;
   // bool check = checkForJump(newSpot);
   // cout << "Check = " << check << endl;
   // while(check != false) {
   //    cout << "What piece do you want to move? -> ";
   //    cin >> curr_piece;
   //    cout << "Where do you want to move? -> ";
   //    cin >> future_spot;
   //    cout << endl;

   //    curr_piece_position = getCoordinates(curr_piece);
   //    future_spot_position = getCoordinates(future_spot);

   //    movePiece(curr_piece_position, future_spot_position);
   //    check = checkForJump(newSpot);
   // }

   // cout << "End of current players turn\n\n";

}

bool Game::checkForJump(Position position){
   Position down_left_B;
   down_left_B.row = position.row - 1;
   down_left_B.column = position.column - 1;
   Position down_right_B;
   down_right_B.row = position.row - 1;
   down_right_B.column = position.column + 1;
   Position up_left_W;
   up_left_W.row = position.row + 1;
   up_left_W.column = position.column - 1;
   Position up_right_W;
   up_right_W.row = position.row + 1;
   up_right_W.column = position.column + 1;

   bool jump_left = false;
   bool jump_right = false;
   //Check if the piece is a king piece :: TODO LATER

   //No kings yet, so only need to check "forward" of the piece
   //Find out what piece we're checking for to know which direction to check
   char piece = getPieceAtPosition(position);
   cout << "Piece in checkForJump: " << piece << endl;
   cout << "   Coordinates of piece -> Row: " << position.row << ", Column: " << position.column << endl;
   if(piece == 'B'){
      cout << "\nIn piece == 'B'\n";
      // Check for B -> down_left
      if(getPieceAtPosition(down_left_B) == 'W'){
         // cout << "In down_left_B == 'W'\n";
         //Also need to check that spot where piece will land is clear
         // cout << "   OG down_left_B coordinates -> Row: " << down_left_B.row << ", Column: " << down_left_B.column << endl; 
         // down_left_B.row--;
         // down_left_B.column--;
         down_left_B.row--;
         down_left_B.column--;
         // cout << "   New down_left_B coordinates -> Row: " << down_left_B.row << ", Column: " << down_left_B.column << endl;
         if(getPieceAtPosition(down_left_B) != 0x20){
            cout << "   Can not jump down_left\n";
            jump_left = false;
         }
         else {
            cout << "   Can jump down_left\n";
            jump_left = true;
         }
      }
      // Check for B -> down_right
      if(getPieceAtPosition(down_right_B) == 'W'){
         // cout << "In down_right_B == 'W'\n";
         //Also need to check that spot where piece will land is clear
         // cout << "   OG down_right_B coordinates -> Row: " << down_right_B.row << ", Column: " << down_right_B.column << endl; 
         // down_right_B.row--;
         // down_right_B.column++;
         down_right_B.row--;
         down_right_B.column++;
         // cout << "   New down_right_B coordinates -> Row: " << down_right_B.row << ", Column: " << down_right_B.column << endl;
         if(getPieceAtPosition(down_right_B) != 0x20){
            cout << "   Can not jump down_right\n";
            jump_right = false;
         }
         else {
            cout << "   Can jump down_right\n";
            jump_right = true;
         }
      }
   }
   else if(piece == 'W'){
      cout << "In piece == 'W'\n";
      // cout << "   Coordinates of piece -> Row: " << position.row << ", Column: " << position.column << endl;
      // Check for W -> up_left
      // cout << "   Piece up_left: " << getPieceAtPosition(up_left_W) << endl;
      if(getPieceAtPosition(up_left_W) == 'B'){
         // cout << "In up_left_W == 'B'\n";
         //Also need to check that spot where piece will land is clear
         // up_left_W.row++;
         // up_left_W.column--;
         // cout << "   OG up_left_W coordinates -> Row: " << up_left_W.row << ", Column: " << up_left_W.column << endl; 
         up_left_W.row--;
         up_left_W.column++;
         // cout << "   New up_left_W coordinates -> Row: " << up_left_W.row << ", Column: " << up_left_W.column << endl;
         if(getPieceAtPosition(up_left_W) != 0x20){
            cout << "   Can not jump up_left\n";
            jump_left = false;
         } 
         else {
            cout << "   Can jump up_left\n";
            jump_left = true;
         }
      }
      // check for W -> up_right
      // cout << "   Piece up_right: " << getPieceAtPosition(up_right_W) << endl;
      if(getPieceAtPosition(up_right_W) == 'B'){
         // cout << "In up_right_W == 'B'\n";
         //Also need to check that spot where piece will land is clear
         // cout << "   OG up_right_W coordinates -> Row: " << up_right_W.row << ", Column: " << up_right_W.column << endl;
         // up_right_W.row--;
         // up_right_W.column--;
         up_right_W.row++;
         up_right_W.column++;
         // cout << "   New up_right_W coordinates -> Row: " << up_right_W.row << ", Column: " << up_right_W.column << endl;
         if(getPieceAtPosition(up_right_W) != 0x20){
            cout << "   Can not jump up_right\n";
            jump_right = false;
         } 
         else {
            cout << "   Can jump up_right\n";
            jump_right = true;
         }
      }
   }
   else{
      cout << "ERROR in checkForJump function\n";
      return false;
   }
   // if(jump_left == false && jump_right == false) {
   //    // cout << "jump_left = " << jump_left << ", jump_right = " << jump_right << endl;
   //    cout << "Can NOT jump either direction\n";
   // }
   return jump_left || jump_right;
}

bool Game::checkForCurrentPlayerJump(Position position, char curr_player){
   Position down_left_B;
   down_left_B.row = position.row - 1;
   down_left_B.column = position.column - 1;
   Position down_right_B;
   down_right_B.row = position.row - 1;
   down_right_B.column = position.column + 1;
   Position up_left_W;
   up_left_W.row = position.row + 1;
   up_left_W.column = position.column - 1;
   Position up_right_W;
   up_right_W.row = position.row + 1;
   up_right_W.column = position.column + 1;
   cout << getPieceAtPosition(position) << ", " << curr_player << endl;

   Position player;
   bool jump = false;
   bool flag = false;

   if(getPieceAtPosition(position) != curr_player){
      cout << "Here1\n";
      // Need to find position of curr_player in relation to position
      // Then checkForJump(curr_player Position)
      if(getPieceAtPosition(down_left_B)  == curr_player){
         cout << "Here2\n";
         player = down_left_B;
         flag = true;
      } else if(getPieceAtPosition(down_right_B) == curr_player){
         cout << "Here3\n";
         player = down_right_B;
         flag = true;
      } else if(getPieceAtPosition(up_left_W)    == curr_player){
         cout << "Here4\n";
         player = up_left_W;
         flag = true;
      } else if(getPieceAtPosition(up_right_W)   == curr_player){
         cout << "Here5\n";
         player = up_right_W;
         flag = true;
      }
      if(flag = true) {
         cout << "Here6\n";
         jump = checkForJump(player);
         cout << "Here6 again\n";
         return jump;
      }
   } else {
      cout << "Here7\n";
      return jump;
   }
   return false;
};

char Game::getPieceAtPosition(Position position){
   return board[position.row][position.column];
}

void Game::setPieceAtPosition(Position position, char c){
   board[position.row][position.column] = c;
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
   cout << "   A     B     C     D     E     F     G     H\n\n";
}

char Game::changeCurrentPlayer(char player){
   // cout << "In changeCurrentPlayer()\n";
   if(player == 'B') {
      // cout << "current_player = B\n";
      player = 'W';
   } else{
      // cout << "current_player = W\n";
      player = 'B';
   }
   return player;
}

