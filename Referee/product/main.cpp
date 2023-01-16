#include <iostream>
#include  "referee.h"

using namespace std;

Referee ref;

void DisplayBoard(char chessboard[ROW_SIZE][COLUMN_SIZE]){
    cout << endl;
    for (int i = 0; i < ROW_SIZE; i++)
    {
        for(int j = 0; j < COLUMN_SIZE; j++)
        {
            cout << chessboard[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}
void FillBoard(char chessboard[ROW_SIZE][COLUMN_SIZE]){
    // white= p: pawn, r: rook, n: knight, b: bishop, q: queen, k: king
    // black= P: pawn, R: rook, N: knight, B: bishop, Q: queen, K: king
    // white
    chessboard[0][Referee::a] = 'r';
    chessboard[0][Referee::b] = 'n';
    chessboard[0][Referee::c] = 'b';
    chessboard[0][Referee::d] = 'q';
    chessboard[0][Referee::e] = 'k';
    chessboard[0][Referee::f] = 'b';
    chessboard[0][Referee::g] = 'n';
    chessboard[0][Referee::h] = 'r';
    for(int i = 0; i < ROW_SIZE; i++){
        chessboard[1][i] = 'p';
    }
    // blackcl
    chessboard[7][Referee::a] = 'R';
    chessboard[7][Referee::b] = 'N';
    chessboard[7][Referee::c] = 'B';
    chessboard[7][Referee::d] = 'Q';
    chessboard[7][Referee::e] = 'K';
    chessboard[7][Referee::f] = 'B';
    chessboard[7][Referee::g] = 'N';
    chessboard[7][Referee::h] = 'R';
    for(int i = 0; i <ROW_SIZE ; i++){
        chessboard[Referee::g][i] = 'P';
    }

    //fill empty spaces with '_'
    for(int i = 2; i < 6; i++){
        for(int j = 0; j < COLUMN_SIZE; j++){
            chessboard[i][j] = '_';
        }
    }
}
/*
    Valid King move, if the piece moves from (X1, Y1) to (X2, Y2), the move is valid if and only if |X2-X1|<=1 and |Y2-Y1|<=1.

    Valid Bishop move, if the piece moves from (X1, Y1) to (X2, Y2), the move is valid if and only if |X2-X1|=|Y2-Y1|.

    Valid Rook move, if the piece moves from (X1, Y1) to (X2, Y2), the move is valid if and only if X2=X1 or Y2=Y1.

    Valid Queen move, a queen's move is valid if it is either a valid bishop or rook move.

    Valid Knight move, if the piece moves from (X1, Y1) to (X2, Y2), the move is valid if and only if (|X2-X1|=1 and |Y2-Y1|=2) or (|X2-X1|=2 and |Y2-Y1|=1).

    Valid Pawn move, if the piece moves from (X1, Y1) to (X2, Y2), the move is valid if and only if X2=X1 and Y2-Y1=1 (only for a white pawn).
*/

int main(){
    char chessboard[ROW_SIZE][COLUMN_SIZE] = {};
    FillBoard(chessboard);
    DisplayBoard(chessboard);
    char chessboardmove[5] = "";
    while(1){
        cout << "Enter move: ";
        cin >> chessboardmove;
        if(ref.CheckIfMoveAllowed(chessboard, chessboardmove) == 0){
            cout << "Invalid move" << endl;
            continue;
        }
        ref.tColor = (ref.tColor == Referee::WHITE) ? Referee::BLACK : Referee::WHITE;
        cout << ref.tColor << endl;
        ref.PlayMove(chessboard, chessboardmove);
        DisplayBoard(chessboard);
    }

    return 0;
}


