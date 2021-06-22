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
        // bool check = game.checkForJump(game.newSpot);
        // cout << "Check = " << check << endl;
        if(checkers.jumpedAPiece == true){
            //The player just jumped a piece, so it's still their turn
            bool check = game.checkForJump(game.newSpot);

            while(check != false) { //loop while current piece can still jump
                board.printBoard(game);
                if(check == true) cout << "Piece available to jump. Go again.\n";
            
                game.turn();
                check = game.checkForJump(game.newSpot);
            }
        }
        
        cout << "End of current players turn\n---------------------------------------\n";
        // cout << "---------------------------------------" << endl;
        board.printBoard(game);
        // menu.printScore(game); //Don't want that option right now
        game_over = game.gameOver();
        if(!game_over) cout << "Next player's turn.\n";
    }

    game.getWinner();

    // board.printBoard(game);
    return -1;
}