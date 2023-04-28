#ifndef PUZZLE_H_INCLUDED
#define PUZZLE_H_INCLUDED

#include <iostream>
#include "edgeloader.h"
#include "piece.h"
#include "picture.h"

class Puzzle{
    private: 
        Picture* picture;
        Piece*** pieceTable; //2d array of piece pointers
        EdgeLoader edgeLoader;
        int numAcross;
        int numDown;
     public:
        Puzzle(string filename);
        ~Puzzle();
        void draw(Drawer &drawer);
        //window.mouseClick()
        bool mouseClick(point p, Piece** selectedPiece);

};
#endif //PUZZLE_H_INCLUDED
