#ifndef PUZZLE_H_INCLUDED
#define PUZZLE_H_INCLUDED

#include <iostream>
#include "piece.h"
#include "picture.h"

class Puzzle{
    private: 
        Picture* picture;
        Picture* edge; //temporary edge
        Piece*** pieceTable; //2d array of piece pointers
        int numAcross;
        int numDown;
     public:
        Puzzle(string filename);
        ~Puzzle();
        void draw(Drawer &drawer);
        //window.mouseClick()
        bool mouseClick();
};
#endif //PUZZLE_H_INCLUDED
