#ifndef PICTURE_H_INCLUDED
#define PICTURE_H_INCLUDED

#include "SDL_Plotter.h"
#include "vec2.h"
#include <fstream>

class Picture {
    public:
        int width, height;
        color *
            *picData; // 2d array that contains color of each pixel in picture
        Picture(string filename);
        ~Picture();
        Vec2 dim();
        color getPixel(int x, int y);
};

enum Orientation { NORMAL, RIGHT, FLIPPED, LEFT };

class Drawer {
    public:
        static void drawPicture(Picture &pic, SDL_Plotter &g, Vec2 pos,
                                Orientation orient = NORMAL);
        static void drawMask(Picture &pic, Picture &mask, Vec2 maskStart,
                             SDL_Plotter &g, Vec2 pos,
                             Orientation orient = NORMAL);
    private:
        static void topOrientationDraw(Picture &pic, SDL_Plotter &g, Vec2 pos);
        static void rightOrientationDraw(Picture &pic, SDL_Plotter &g,
                                         Vec2 pos);
        static void flippedOrientationDraw(Picture &pic, SDL_Plotter &g,
                                           Vec2 pos);
        static void leftOrientationDraw(Picture &pic, SDL_Plotter &g, Vec2 pos);
        static void topOrientationMask(Picture &pic, Picture &mask, Vec2 maskStart,
                             SDL_Plotter &g, Vec2 pos,
                             Orientation orient = NORMAL);
        static void rightOrientationMask(Picture &pic, Picture &mask, Vec2 maskStart,
                             SDL_Plotter &g, Vec2 pos,
                             Orientation orient = NORMAL);
        static void flippedOrientationMask(Picture &pic, Picture &mask, Vec2 maskStart,
                             SDL_Plotter &g, Vec2 pos,
                             Orientation orient = NORMAL);
        static void leftOrientationMask(Picture &pic, Picture &mask, Vec2 maskStart,
                             SDL_Plotter &g, Vec2 pos,
                             Orientation orient = NORMAL);
};
#endif // PICTURE_H_INCLUDED
