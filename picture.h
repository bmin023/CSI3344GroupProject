#ifndef PICTURE_H_INCLUDED
#define PICTURE_H_INCLUDED

#include "SDL_Plotter.h"
#include <fstream>


class Picture{
    public:
        int width, height;
        color** picData;  //2d array that contains color of each pixel in picture
        Picture(string filename);
        ~Picture();
};

#endif // PICTURE_H_INCLUDED