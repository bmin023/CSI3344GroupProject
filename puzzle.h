#ifndef PUZZLE_H_INCLUDED
#define PUZZLE_H_INCLUDED

#include <iostream>
#include "edgeloader.h"
#include "piece.h"
#include "picture.h"

class Puzzle{
    private: 
        Picture picture;
        Piece*** pieceTable; //2d array of piece pointers
        EdgeLoader edgeLoader;
        int numAcross;
        int numDown;
     public:
        Puzzle(string filename, int maxHeight = 1000, int maxWidth = 1000);
        Puzzle() {}
        Puzzle(const Puzzle& other);
        Puzzle& operator=(const Puzzle& other);
        ~Puzzle();
        void draw(Drawer &drawer);
        //window.mouseClick()
        bool mouseClick(point p, Piece** selectedPiece);
        int pieces() {return numAcross * numDown;}
};
#endif //PUZZLE_H_INCLUDED
