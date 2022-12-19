#include <iostream>
#include "Referee.h"

using namespace std;

char Referee::PieceAt(char chessboard[][COLUMN_SIZE], char pos[MIN_MOVE_SIZE]){
    char tempLetter = pos[0];
    int  tempNr = ((((int)pos[1] - 48)*10) + ((int)pos[2] -48) -49); //goofy code om 2 char uit pos te veranderen naar een int
    cout << "tempnr: "<< tempNr << endl;
    chessboard_collumns currCol = static_cast<chessboard_collumns>(tempLetter); //97 want ja dan werkt t eenmaal
    cout << "currcol: " << (currCol-97) << endl;
    return chessboard[tempNr][currCol-97];
   
}

int Referee::CheckMove(char chessboard[][COLUMN_SIZE] , char move[MAX_MOVE_SIZE], char* msg, int max_size){
    
    char posPiece[MIN_MOVE_SIZE];
    sprintf(posPiece, "%c%d", move[0], move[1]);

    cout <<"pospiece: "<< posPiece << endl;
    char currPiece = PieceAt(chessboard, posPiece);
    cout <<"curpiece: "<< currPiece << endl;
    return 1;
}

int Referee::PlayMove(char chessboard[][COLUMN_SIZE] , char move[MAX_MOVE_SIZE]){
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