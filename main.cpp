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
    game.newGame();
    game.current_player = 'B'; //Black pieces always goes first
    game.newSpot.row = 7;      //Initialize newSpot
    game.newSpot.column = 7;   // 
    board.printBoard(game);
    game_over = false;
    while(game_over != true){

        // bool check = game.checkForJump(game.newSpot);   //Need to change to a function that checks for a jump at the beginning of a turn
        //                                                 // ..maybe something that just checks around the last piece that jumped to find if it's by the other color
        //                                                 // then check if it can jump
        bool check2 = game.checkForCurrentPlayerJump(game.newSpot, game.current_player);
        if(check2 == true){
            cout << "Piece available to jump, you must jump\n";
        }

        bool move = game.turn();
        while (move != true){ //While move success is not true
            move = game.turn();
        }
        // bool check = game.checkForJump(game.newSpot);
        // cout << "Check = " << check << endl;
        while(game.jumpedAPiece == true){
            //The player just jumped a piece, so it's still their turn
            cout << "You jumped a piece, go again\n";
            board.printBoard(game);
            bool check = game.checkForJump(game.newSpot);

            while(check != false) { //loop while current piece can still jump
                board.printBoard(game);
                if(check == true) cout << "Piece available to jump. You must jump.\n";
            
                game.turn();
                check = game.checkForJump(game.newSpot);
            }
            game.turn();
        }
        
        cout << "End of Player " << game.current_player << "'s turn\n---------------------------------------\n";
        // cout << "---------------------------------------" << endl;
        board.printBoard(game);
        // menu.printScore(game); //Don't want that option right now
        game_over = game.gameOver();
        game.current_player = game.changeCurrentPlayer(game.current_player);
        if(!game_over) cout << "It is Player " << game.current_player << "'s turn.\n";
    }

    game.getWinner();

    // board.printBoard(game);
    return -1;
}