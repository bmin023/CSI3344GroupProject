#ifndef PUZZLE_H_INCLUDED
#define PUZZLE_H_INCLUDED

#include <iostream>
#include "piece.h"
#include "picture.h"

class Puzzle{
    private: 
        Picture* picture;
        Piece*** pieceTable; //2d array of piece pointers
     public:
        Puzzle(string filename);
        //window.mouseClick()
        bool mouseClick();

};
#endif //PUZZLE_H_INCLUDED