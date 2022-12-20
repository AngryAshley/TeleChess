#include <iostream>
#include "Referee.h"

using namespace std;

char Referee::PieceAt(char chessboard[][COLUMN_SIZE], char pos[MIN_MOVE_SIZE]){
    char tempLetter = pos[0];
    int  tempNr = ((((int)pos[1] - 48)*10) + ((int)pos[2] -48) -49); //goofy code om 2 char uit pos te veranderen naar een int
    chessboard_collumns currCol = static_cast<chessboard_collumns>(tempLetter); //97 want ja dan werkt t eenmaal
    return chessboard[tempNr][currCol-97];
   
}

int Referee::CheckMove(char chessboard[][COLUMN_SIZE] , char move[MAX_MOVE_SIZE]){
    char posPiece[MIN_MOVE_SIZE];
    sprintf(posPiece, "%c%d", move[0], move[1]);
    char currPiece = PieceAt(chessboard, posPiece);
    int returnval;
    switch (currPiece){
        case 'r':
        case 'R':
            //check if move is valid for rook
            returnval = (move[0] == move[2] || move[1] == move[3]);
            break;
        case 'n':
        case 'N':
        {
            int dx = abs(move[0] - move[2]);
            int dy = abs(move[1] - move[3]);
            returnval = ((dx == 2 && dy == 1) || (dx == 1 && dy == 2));
            break;
        }
        case 'b':
        case 'B':
            //check if move is valid for bishop
            returnval = (move[0] - move[2] == move[1] - move[3]);
            break;
        
        case 'q':
        case 'Q':
            //check if move is valid for queen
            returnval = ((move[0] == move[2] || move[1] == move[3] || abs(move[0] - move[2]) == abs(move[1] - move[3])));
            break;
        case 'k':
        case 'K':
        {
            int dx = abs(move[0] - move[2]);
            int dy = abs(move[1] - move[3]);
            returnval = (dx <= 1 && dy <= 1);
            break;
        }
        case 'p':
        case 'P':
        {
            
        }
        default:
            returnval = -1;
            break;
    }   
    return returnval;
}

int Referee::PlayMove(char chessboard[][COLUMN_SIZE] , char move[MAX_MOVE_SIZE]){
    int from_row = move[1] - '0' - 1;
    int from_col = move[0] - 'a';
    int to_row = move[3] - '0' - 1;
    int to_col = move[2] - 'a';
    if(chessboard[from_row][from_col] == '_'){
        cout << "No piece at that location" << endl;
        return -1;
    }
    int outputmove = CheckMove(chessboard, move);
    if(outputmove != 1 ){
        cout << "Move not valid" << endl;
        return 0;
    }
    chessboard[to_row][to_col] = chessboard[from_row][from_col];
    chessboard[from_row][from_col] = '_';
    return 1;
}