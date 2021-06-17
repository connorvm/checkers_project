#include "checkers.h"
#include <iostream>

using namespace std;

Board board;
Game game;
Checkers checkers;


int main() {
    cout << "Welcome to checkers!\n\n";
    bool game_over = game.gameOver();
    int choice;
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

        // cout << "What piece do you want to move? Row, column -> ";
        // cin >> curr_row >> curr_column;
        // cout << "Where do you want to move? Row, column -> ";
        // cin >> row >> column;
        // cout << endl;
        game.turn();
        // game.movePiece(curr_row, curr_column, row, column);
        // game.printBoard();
        board.printBoard(game);
        game_over = game.gameOver();
    }

    game.getWinner();

    // board.printBoard(game);
    return -1;
}