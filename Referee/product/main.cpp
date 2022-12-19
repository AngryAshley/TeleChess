#include <iostream>
#include  "referee.h"

using namespace std;

Referee ref;
enum turnColor{ 
    BLACK, 
    WHITE, 
    NONE};

void DisplayBoard(char chessboard[ROW_SIZE][COLUMN_SIZE]){
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
    chessboard[0][ref.a] = 'r';
    chessboard[0][ref.b] = 'n';
    chessboard[0][ref.c] = 'b';
    chessboard[0][ref.d] = 'q';
    chessboard[0][ref.e] = 'k';
    chessboard[0][ref.f] = 'b';
    chessboard[0][ref.g] = 'n';
    chessboard[0][ref.h] = 'r';
    for(int i = 0; i < ROW_SIZE; i++){
        chessboard[1][i] = 'p';
    }
    // blackcl
    chessboard[7][ref.a] = 'R';
    chessboard[7][ref.b] = 'N';
    chessboard[7][ref.c] = 'B';
    chessboard[7][ref.d] = 'Q';
    chessboard[7][ref.e] = 'K';
    chessboard[7][ref.f] = 'B';
    chessboard[7][ref.g] = 'N';
    chessboard[7][ref.h] = 'R';
    for(int i = 0; i <ROW_SIZE ; i++){
        chessboard[ref.g][i] = 'P';
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

    char chessboardmove[5] = "a8b4";
    //char chessboardmove2[5] = "g7c5";

    cout << "Before move " << chessboardmove <<":" << endl;
    DisplayBoard(chessboard);
    ref.PlayMove(chessboard, chessboardmove);
    
    cout << "After  move:" << endl;
    DisplayBoard(chessboard);
    
    // cout << "Before move " << chessboardmove2 <<":" << endl;
    // PlayMove(chessboard, chessboardmove2);
    
    // cout << "After  move:" << endl;
    // DisplayBoard(chessboard);

    return 0;
}


