#ifndef PIECE_H_INCLUDED
#define PIECE_H_INCLUDED

#include "SDL_Plotter.h"
#include "picture.h"

class Piece{
    private:
    Picture* image;
    Piece *topNeighbor, *bottomNeighbor, *lNeighbor, *rNeighbor;
    Piece* neighborArr [4] = {nullptr, nullptr, nullptr, nullptr}; //neighbor array
    int orientation;
    //Edge *topEdge, *bottomEdge, *lEdge, *rEdge;
    int startX, startY;  //start coordinates

    public:
    Piece();


};

#endif // PIECE_H_INCLUDED
