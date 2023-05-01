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
        Edge& operator=(const Edge &other);
        color getPixel(int x, int y) override;
};

class Piece{
    private:
    bool moved = false;
    Picture& image;
    Vec2 imagePos;
    Piece* neighborArr [4] = {nullptr, nullptr, nullptr, nullptr}; //neighbor array
    bool connected [4] = {false, false, false, false}; //connected array
    Orientation orientation;
    Edge topEdge, bottomEdge, lEdge, rEdge;
    Vec2 pos;
    int ping(int count);

    public:
    Piece(const Piece &other) : pos(other.pos), imagePos(other.imagePos), image(other.image) {
        cout << "copy constructor" << endl;
        moved = other.moved;
        for(int i = 0; i< 4; i++) {
            neighborArr[i] = other.neighborArr[i];
            connected[i] = other.connected[i];
        }
        orientation = other.orientation;
        cout << "I am at the edges." << endl;
        topEdge = other.topEdge;
        cout << "first edge" << endl;
        bottomEdge = other.bottomEdge;
        lEdge = other.lEdge;
        rEdge = other.rEdge;
        cout << "done" << endl;
    }
    int getConnected();
    void connect(Orientation orient);
    void setMoved(bool moved);
    bool isSnappable(Orientation orient);
    void setConnected(Orientation orient, bool connected);
    Vec2 snap(Orientation orient);
    void move(Vec2 newPos, Drawer& drawer, Picture& bg);
    int thing = rand() % 100;
    void setPos(const Vec2 &newPos);
    Vec2 getPos() const;
    bool isClicked(point p);
    Piece(Picture& image, Vec2 imagePos, Vec2 pos);
    void draw(Drawer& drawer);
    void draw(Drawer& drawer, Picture& pic);
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
