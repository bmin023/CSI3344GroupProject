#ifndef PIECE_H_INCLUDED
#define PIECE_H_INCLUDED

#include "SDL_Plotter.h"
#include "picture.h"
#include "vec2.h"

class Edge : public Picture {
    private:
        bool inverted;
    public:
        Edge(Picture &pic, bool inverted = false);
        Edge();
        ~Edge() override;
        Edge operator=(const Edge &other);
        color getPixel(int x, int y) override;
};

class Piece{
    private:
    Picture& image;
    Vec2 imagePos;
    Piece* neighborArr [4] = {nullptr, nullptr, nullptr, nullptr}; //neighbor array
    Orientation orientation;
    Edge topEdge, bottomEdge, lEdge, rEdge;
    Vec2 pos;

    public:
    bool isClicked(point p);
    Piece(Picture& image, Vec2 imagePos, Vec2 pos);
    void draw(Drawer& drawer);
    void setEdge(Orientation orient, Edge edge) {
        switch(orient) {
            case NORMAL:
                topEdge = edge;
                break;
            case RIGHT:
                rEdge = edge;
                break;
            case FLIPPED:
                bottomEdge = edge;
                break;
            case LEFT:
                lEdge = edge;
                break;
        }
    }
    void setNeighbor(int index, Piece* neighbor);
};

#endif // PIECE_H_INCLUDED
