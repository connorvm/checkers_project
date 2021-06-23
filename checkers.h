#include <string>
#include <iostream>
#include "stdlib.h"
using namespace std;

class Checkers {
    public:
        static bool isWhitePiece();
        static bool isBlackPiece();

        const char initial_board[8][8] = 
        {
            {'W',  0x20, 'W',  0x20, 'W',  0x20, 'W',  0x20}, //Bottom of printed board
            {0x20, 'W',  0x20, 'W',  0x20, 'W',  0x20, 'W'},
            {'W',  0x20, 'W',  0x20, 'W',  0x20, 'W',  0x20},
            {0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20},
            {0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20},
            {0x20, 'B',  0x20, 'B',  0x20, 'B',  0x20, 'B'},
            {'B',  0x20, 'B',  0x20, 'B',  0x20, 'B',  0x20},
            {0x20, 'B',  0x20, 'B',  0x20, 'B',  0x20, 'B'}
        };

        struct Position 
        {
            int row;
            int column;
        };

        const Position white_spaces[32] = 
        {
            {0,1}, {0,3}, {0,5}, {0,7},
            {1,0}, {1,2}, {1,4}, {1,6},
            {2,1}, {2,3}, {2,5}, {2,7},
            {3,0}, {3,2}, {3,4}, {3,6},
            {4,1}, {4,3}, {4,5}, {4,7},
            {5,0}, {5,2}, {5,4}, {5,6},
            {6,1}, {6,3}, {6,5}, {6,7},
            {7,0}, {7,2}, {7,4}, {7,6},
        };

        enum Direction {    
            Up_Left = 0,      //|0|| ||1|  
            Up_Right = 1,     //| ||W|| |  
            Down_Left = 2,    //|2|| ||3|  
            Down_Right = 3      
        };

};

class Game : Checkers{
    public:
        char getColorPieceAtPosition(int row, int column);
        void newGame();
        bool gameOver();
        char getWinner();
        int numberOfJumpedB = 0;
        int numberOfJumpedW = 0;
        Position newSpot;
        Position previousPiece;
        Position curr_piece_position;
        Position future_spot_position;
        bool jumpedAPiece;

        //for quicker testing, print out simple board
        void printBoard();

        bool movePiece(Position present, Position future);
        void movePiece(int curr_row, int curr_column, int row, int column);
        // enum Direction getDirectionOfMovingPiece();
        char getPieceAtPosition(Position position);
        void setPieceAtPosition(Position position, char c);
        Position getCoordinates(string spot);
        bool turn();
        bool checkForJump(Position present);

        void printScore();

    private:
        char board[8][8];
};

class Board {
    public:
        void printBoard(Game& game);
        void printLine(int iLine, int iColor1, int iColor2, Game& game);
};

class Menu {
    public:
        void printMenu(){
            int choice;
            cout << "Welcome to Checkers!\n";
            cout << "Would you like to play a game?  [1]Yes    [2]No\n";
            cin >> choice;
            if(choice == 2) {
                cout << "Thanks for stopping by!" << endl;
                exit(0);
            }
            cout << "Let's play!" << endl;
        };

        void printScore(Game& game){
            int choice;
            cout << "Would you like to see the score?  [1]Yes    [2]No\n";
            cin >> choice;
            if(choice == 1) {
                cout << "Number of Jumped B: " << game.numberOfJumpedB << endl;
                cout << "Number of Jumped W: " << game.numberOfJumpedW << endl;
            }
        };
};