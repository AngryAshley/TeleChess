#include <iostream>

#define COLUMN_SIZE 8
#define ROW_SIZE 8
#define MAX_MSG_SIZE 10 
#define MAX_MOVE_SIZE 5
#define MIN_MOVE_SIZE 3

using namespace std;

enum turnColor{ 
    BLACK, 
    WHITE, 
    NONE};
enum chessboard_collumns{
    a,
    b,
    c,
    d,
    e,
    f,
    g,
    h, };
    

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
    chessboard[0][a] = 'r';
    chessboard[0][b] = 'n';
    chessboard[0][c] = 'b';
    chessboard[0][d] = 'q';
    chessboard[0][e] = 'k';
    chessboard[0][f] = 'b';
    chessboard[0][g] = 'n';
    chessboard[0][h] = 'r';
    for(int i = 0; i < ROW_SIZE; i++){
        chessboard[1][i] = 'p';
    }
    // black
    chessboard[7][a] = 'R';
    chessboard[7][b] = 'N';
    chessboard[7][c] = 'B';
    chessboard[7][d] = 'Q';
    chessboard[7][e] = 'K';
    chessboard[7][f] = 'B';
    chessboard[7][g] = 'N';
    chessboard[7][h] = 'R';
    for(int i = 0; i <ROW_SIZE ; i++){
        chessboard[g][i] = 'P';
    }

    //fill empty spaces with '_'
    for(int i = 2; i < 6; i++){
        for(int j = 0; j < COLUMN_SIZE; j++){
            chessboard[i][j] = '_';
        }
    }
}
char PieceAt(char chessboard[][COLUMN_SIZE], char pos[MIN_MOVE_SIZE]){
    int testvar = pos[1];
    cout << pos[0] << pos[1] << pos[2];
    cout << chessboard[testvar][static_cast<chessboard_collumns>(pos[0])];
    return chessboard[testvar][static_cast<chessboard_collumns>(pos[0])];
}

int CheckMove(char chessboard[][COLUMN_SIZE] , char move[MAX_MOVE_SIZE], char* msg, int max_size){
    char posPiece[MIN_MOVE_SIZE];
    char currPiece = PieceAt(chessboard, posPiece);
    cout << currPiece <<endl;
    return 1;
}

int PlayMove(char chessboard[][COLUMN_SIZE] , char move[MAX_MOVE_SIZE]){
    char msg[MAX_MSG_SIZE];
    int from_row = move[1] - '0' - 1;
    int from_col = move[0] - 'a';
    int to_row = move[3] - '0' - 1;
    int to_col = move[2] - 'a';
    if(chessboard[from_row][from_col] == '_'){
        cout << "No piece at that location" << endl;
        return -1;
    }
    int outputmove = CheckMove(chessboard , move, msg, MAX_MSG_SIZE);
    cout << outputmove;
    if(outputmove!= 1 ){
        cout << "Move not valid" << endl;
        return 0;
    }
    chessboard[to_row][to_col] = chessboard[from_row][from_col];
    chessboard[from_row][from_col] = '_';
    return 1;
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

    
    char chessboardmove[5] = "b2b4";
    //char chessboardmove2[5] = "g7c5";

    cout << "Before move " << chessboardmove <<":" << endl;
    DisplayBoard(chessboard);
    PlayMove(chessboard, chessboardmove);
    
    cout << "After  move:" << endl;
    DisplayBoard(chessboard);
    
    // cout << "Before move " << chessboardmove2 <<":" << endl;
    // PlayMove(chessboard, chessboardmove2);
    
    // cout << "After  move:" << endl;
    // DisplayBoard(chessboard);

    return 0;
}


