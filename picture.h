#ifndef PICTURE_H_INCLUDED
#define PICTURE_H_INCLUDED

#include "SDL_Plotter.h"
#include "vec2.h"
#include <assert.h>
#include <fstream>

class Picture {
    public:
        int width, height;
        color **picData; // 2d array that contains color of each pixel in picture
        Picture(string filename);
        Picture(){
            width = 0;
            height = 0;
            picData = nullptr;
        };
        // ~Picture();
        void dealloc();
        Vec2 dim();
        virtual color getPixel(int x, int y);
        int getWidth();
        int getHeight();
};

enum Orientation { NORMAL, RIGHT, FLIPPED, LEFT };

class Drawer {
    public:
        Drawer(SDL_Plotter &g) : g(g) {};
        void drawPicture(Picture &pic, Vec2 pos, Orientation orient = NORMAL);
        void drawMask(Picture &pic, Picture &mask, Vec2 maskStart, Vec2 pos,
                      Orientation orient = NORMAL);
        void drawPart(Picture &pic, Vec2 start, Vec2 dim, Vec2 pos,
                      Orientation orient = NORMAL);

    private:
        SDL_Plotter &g;
        void drawPixel(int x, int y, color c);
        void topOrientationDraw(Picture &pic, Vec2 start, Vec2 dim, Vec2 pos,
                      Orientation orient = NORMAL);
        void rightOrientationDraw(Picture &pic, Vec2 start, Vec2 dim, Vec2 pos,
                      Orientation orient = NORMAL);
        void flippedOrientationDraw(Picture &pic, Vec2 start, Vec2 dim, Vec2 pos,
                      Orientation orient = NORMAL);
        void leftOrientationDraw(Picture &pic, Vec2 start, Vec2 dim, Vec2 pos,
                      Orientation orient = NORMAL);
        void topOrientationMask(Picture &pic, Picture &mask, Vec2 maskStart,
                                Vec2 pos, Orientation orient = NORMAL);
        void rightOrientationMask(Picture &pic, Picture &mask, Vec2 maskStart,
                                  Vec2 pos, Orientation orient = NORMAL);
        void flippedOrientationMask(Picture &pic, Picture &mask, Vec2 maskStart,
                                    Vec2 pos, Orientation orient = NORMAL);
        void leftOrientationMask(Picture &pic, Picture &mask, Vec2 maskStart,
                                 Vec2 pos, Orientation orient = NORMAL);
};
#endif // PICTURE_H_INCLUDED
