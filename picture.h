#ifndef PICTURE_H_INCLUDED
#define PICTURE_H_INCLUDED

#include "SDL_Plotter.h"
#include "vec2.h"
#include <fstream>

class Picture {
public:
  int width, height;
  color **picData; // 2d array that contains color of each pixel in picture
  Picture(string filename);
  ~Picture();
  Vec2 dim();
};

enum Orientation { NORMAL, RIGHT, FLIPPED, LEFT };

class Drawer {
public:
  static void drawPicture(Picture &pic, SDL_Plotter &g, Vec2 pos,
                          Orientation orient = NORMAL);

private:
  static void topOrientationDraw(Picture &pic, SDL_Plotter &g, Vec2 pos);
  static void rightOrientationDraw(Picture &pic, SDL_Plotter &g, Vec2 pos);
  static void flippedOrientationDraw(Picture &pic, SDL_Plotter &g, Vec2 pos);
  static void leftOrientationDraw(Picture &pic, SDL_Plotter &g, Vec2 pos);
};
#endif // PICTURE_H_INCLUDED
