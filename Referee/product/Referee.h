#ifndef REFEREE_H
#define REFEREE_H

#define COLUMN_SIZE     8
#define ROW_SIZE        8
#define MAX_MSG_SIZE    10 
#define MAX_MOVE_SIZE   5
#define MIN_MOVE_SIZE   3

class Referee{
    private:
    public:
        enum turnColor{  
        WHITE,
        BLACK, 
        };

       
        enum chessboard_collumns{
        a,
        b,
        c,
        d,
        e,
        f,
        g,
        h,};

        turnColor tColor;
        Referee ();
        char PieceAt(char chessboard[][COLUMN_SIZE], char pos[MIN_MOVE_SIZE]);
        int CheckCollision(char chessboard[][COLUMN_SIZE] , char move[MAX_MOVE_SIZE]);
        int CheckIfMoveAllowed(char chessboard[][COLUMN_SIZE] , char move[MAX_MOVE_SIZE]);
        int PlayMove(char chessboard[][COLUMN_SIZE] , char move[MAX_MOVE_SIZE]);
        bool SameColor(char chessboard[][COLUMN_SIZE], char move[MAX_MOVE_SIZE]);
};
#endif