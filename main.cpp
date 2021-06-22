#include "checkers.h"
#include <iostream>

using namespace std;

Board board;
Game game;
Checkers checkers;
Menu menu;


int main() {
    // cout << "Welcome to checkers!\n\n";
    bool game_over = game.gameOver();
    menu.printMenu();
    // int choice;  //Used for menu (currently commented out)
    game.newGame();
    board.printBoard(game);
    game_over = false;
    while(game_over != true){

        // cout << "Continue playing? y = 1 or n = 0";
        // cin >> choice;
        // if(choice == 0) {
        //     game_over = true;
        //     break;
        // }

        game.turn();
        bool check = game.checkForJump(game.newSpot);
        // cout << "Check = " << check << endl;

        while(check != false) { //loop while current piece can still jump
            board.printBoard(game);
            if(check == true) cout << "Piece available to jump. Go again.\n";
            // int curr_row, curr_column, row, column;
            // string curr_piece, future_spot;
            // // game.curr_piece_position;
            // // game.future_spot_position;
            // cout << "What piece do you want to move? -> ";
            // cin >> curr_piece;
            // cout << "Where do you want to move? -> ";
            // cin >> future_spot;
            // cout << endl;

            // game.curr_piece_position = game.getCoordinates(curr_piece);
            // game.future_spot_position = game.getCoordinates(future_spot);

            // game.movePiece(game.curr_piece_position, game.future_spot_position);
            game.turn();
            check = game.checkForJump(game.newSpot);
        }

        cout << "End of current players turn\n---------------------------------------\n";
        // cout << "---------------------------------------" << endl;
        board.printBoard(game);
        game_over = game.gameOver();
    }

    game.getWinner();

    // board.printBoard(game);
    return -1;
}