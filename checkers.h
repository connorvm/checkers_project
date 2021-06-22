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

        struct Position {
            int row;
            int column;
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

        //for quicker testing, print out simple board
        void printBoard();

        void movePiece(Position present, Position future);
        void movePiece(int curr_row, int curr_column, int row, int column);
        // enum Direction getDirectionOfMovingPiece();
        char getPieceAtPosition(Position position);
        void setPieceAtPosition(Position position, char c);
        Position getCoordinates(string spot);
        void turn();
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
            cout << "Would you like to play a game?  [1] Yes    [2] No\n";
            cin >> choice;
            if(choice == 2) {
                cout << "Thanks for stopping by!" << endl;
                exit(0);
            }
        };
};