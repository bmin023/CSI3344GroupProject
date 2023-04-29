#ifndef SUPERPIECE_H
#define SUPERPIECE_H

#include "puzzle.h"
#include <vector>
#include "piece.h"
#include "vec2.h"

using namespace std;

class SuperPiece{
    private:
        vector<Piece*> pieces;
    public:
        Vec2 pos;
        SuperPiece(Vec2 pos): pos(pos){};
        void move(Vec2 newPos);
        void eat(SuperPiece& other);
        bool snap();
};



#endif // SUPERPIECE_H