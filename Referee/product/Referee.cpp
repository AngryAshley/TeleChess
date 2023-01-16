#include <iostream>
#include "Referee.h"

using namespace std;

Referee::Referee(){
    tColor = WHITE;
}

char Referee::PieceAt(char chessboard[][COLUMN_SIZE], char pos[MIN_MOVE_SIZE]){
    char tempLetter = pos[0];
    int  tempNr = ((((int)pos[1] - 48)*10) + ((int)pos[2] -48) -49); //goofy code om 2 char uit pos te veranderen naar een int
    chessboard_collumns currCol = static_cast<chessboard_collumns>(tempLetter); //97 want ja dan werkt t eenmaal
    return chessboard[tempNr][currCol-97];
   
}


    //bishop
  
int Referee::CheckCollision(char chessboard[][COLUMN_SIZE] , char move[MAX_MOVE_SIZE]){
    
    int returnval = 1;
    char posPiece[MIN_MOVE_SIZE];
    char posMove[MIN_MOVE_SIZE];
    sprintf(posPiece, "%c%d", move[0], move[1]);
    sprintf(posMove, "%c%d", move[2], move[3]);
        cout<< "turncolor " << tColor << endl;

        char piece = PieceAt(chessboard, posPiece);
        int IsBlack = isupper(piece);
        cout << "isblack " << IsBlack << endl;
        int movedirection; //0 = vertical, 1 = horizontal, 2 = diagonal
        if(move[0] == move[2] && move[1] != move[3]){
            cout << "vertical" << endl;
            movedirection = 0;
        }
        else if(move[0] != move[2] && move[1] == move[3]){
            cout << "horizontal" << endl;
            movedirection = 1;
        }
        else if(move[0] - move[2] == move[1] - move[3]){
            cout << "diagonal" << endl;
            movedirection = 2;
        }       

        //if move is vertical check if going up or down an check if there is a piece in the way
        if(movedirection == 0){
            if(move[1] < move[3]){
                for(int i = move[1] + 1; i < move[3]; i++){
                    sprintf(posPiece, "%c%d", move[0], i);
                    if(PieceAt(chessboard, posPiece) != '_'){
                        returnval = 0;
                    }
                }
            }
            else if(move[1] > move[3]){
                for(int i = move[1] - 1; i > move[3]; i--){
                    sprintf(posPiece, "%c%d", move[0], i);
                    if(PieceAt(chessboard, posPiece) != '_'){
                        returnval = 0;
                    }
                }
            }
        }

        //if mov eis horizontal check if going left or right and check if there is a piece in the way
        else if(movedirection == 1){
            if(move[0] < move[2]){
                for(int i = move[0] + 1; i < move[2]; i++){
                    sprintf(posPiece, "%c%d", i, move[1]);
                    if(PieceAt(chessboard, posPiece) != '_'){
                        returnval = 0;
                    }
                }
            }
            else if(move[0] > move[2]){
                for(int i = move[0] - 1; i > move[2]; i--){
                    sprintf(posPiece, "%c%d", i, move[1]);
                    if(PieceAt(chessboard, posPiece) != '_'){
                        returnval = 0;
                    }
                }
            }
        }

        //if move is diagonal check if going up or down and check if there is a piece in the way
        else if(movedirection == 2){
            if(move[0] < move[2] && move[1] < move[3]){
                for(int i = move[0] + 1, j = move[1] + 1; i < move[2] && j < move[3]; i++, j++){
                    sprintf(posPiece, "%c%d", i, j);
                    if(PieceAt(chessboard, posPiece) != '_'){
                        returnval = 0;
                    }
                }
            }
            else if(move[0] > move[2] && move[1] > move[3]){
                for(int i = move[0] - 1, j = move[1] - 1; i > move[2] && j > move[3]; i--, j--){
                    sprintf(posPiece, "%c%d", i, j);
                    if(PieceAt(chessboard, posPiece) != '_'){
                        returnval = 0;
                    }
                }
            }
            else if(move[0] < move[2] && move[1] > move[3]){
                for(int i = move[0] + 1, j = move[1] - 1; i < move[2] && j > move[3]; i++, j--){
                    sprintf(posPiece, "%c%d", i, j);
                    if(PieceAt(chessboard, posPiece) != '_'){
                        returnval = 0;
                    }
                }
            }
            else if(move[0] > move[2] && move[1] < move[3]){
                for(int i = move[0] - 1, j = move[1] + 1; i > move[2] && j < move[3]; i--, j++){
                    sprintf(posPiece, "%c%d", i, j);
                    if(PieceAt(chessboard, posPiece) != '_'){
                        returnval = 0;
                    }
                }
            }
        }

        return returnval;   
    }


int Referee::CheckIfMoveAllowed(char chessboard[][COLUMN_SIZE] , char move[MAX_MOVE_SIZE]){
    char posPiece[MIN_MOVE_SIZE];
    sprintf(posPiece, "%c%d", move[0], move[1]);
    char currPiece = PieceAt(chessboard, posPiece);
    int returnval;
    switch (currPiece){
        case 'r':
        case 'R':
            //check if move is valid for rook
            returnval = (move[0] == move[2] || move[1] == move[3]);
             if(CheckCollision(chessboard, move) == 0){
                returnval = 0;
            }
            break;
        case 'n':
        case 'N':
        {
            int dx = abs(move[0] - move[2]);
            int dy = abs(move[1] - move[3]);
            returnval = ((dx == 2 && dy == 1) || (dx == 1 && dy == 2));
             if(CheckCollision(chessboard, move) == 0){
                returnval = 0;
            }
            break;
        }
        case 'b':
        case 'B':
            //check if move is valid for bishop
            returnval = (move[0] - move[2] == move[1] - move[3]);
            if(CheckCollision(chessboard, move) == 0){
                returnval = 0;
            }
            break;
        
        case 'q':
        case 'Q':
            //check if move is valid for queen
            returnval = ((move[0] == move[2] || move[1] == move[3] || abs(move[0] - move[2]) == abs(move[1] - move[3])));
             if(CheckCollision(chessboard, move) == 0){
                returnval = 0;
            }
            break;
        case 'k':
        case 'K':
        {
            int dx = abs(move[0] - move[2]);
            int dy = abs(move[1] - move[3]);
            returnval = (dx <= 1 && dy <= 1);
             if(CheckCollision(chessboard, move) == 0){
                returnval = 0;
            }
            break;
        }
        case 'p':
        {
            returnval = (move[0] == move[2] && (move[3] - move[1] == 1));
             if(CheckCollision(chessboard, move) == 0){
                returnval = 0;
            }
            break;
        }   
        case 'P': 
        {
            returnval = (move[0] == move[2] && (move[3] - move[1] == -1));
             if(CheckCollision(chessboard, move) == 0){
                returnval = 0;
            }
            break;
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
    int outputmove = CheckIfMoveAllowed(chessboard, move);
    printf("outputmove: %d \n", outputmove);
    if(outputmove != 1 ){
        cout << "Move not valid" << endl;
        return 0;
    }
    chessboard[to_row][to_col] = chessboard[from_row][from_col];
    chessboard[from_row][from_col] = '_';
    return 1;
}