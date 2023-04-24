#include "picture.h"
#include "SDL_Plotter.h"
#include "vec2.h"
#include <cassert>

Picture::Picture(string filename) {
    ifstream input;
    input.open(filename);
    if (!input) {
        cerr << "ERROR COULD NOT OPEN FILE";
    } else {
        input >> this->height;
        input >> this->width;

        picData = new color *[height];
        for (int i = 0; i < height; i++) {
            picData[i] = new color[width];
        }

        int R, G, B;
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (input >> R >> G >> B) {
                    // plotPixel(int x, int y, int r, int g, int b) - plots a
                    // single pixel at location (x,y) and color (r,g,b)
                    color pixel;
                    pixel.R = R;
                    pixel.G = G;
                    pixel.B = B;

                    picData[i][j] = pixel;
                }
            }
        }
        input.close();
    }
}

Picture::~Picture() {
    for (int i = 0; i < height; i++) {
        delete[] picData[i];
    }

    delete[] picData;
}

color Picture::getPixel(int x, int y) { return picData[x][y]; }

Vec2 Picture::dim() { return Vec2(width, height); }

void Drawer::drawPicture(Picture &pic, SDL_Plotter &g, Vec2 pos,
                         Orientation orient) {
    switch (orient) {
    case NORMAL:
        Drawer::topOrientationDraw(pic, g, pos);
        break;
    case RIGHT:
        Drawer::rightOrientationDraw(pic, g, pos);
        break;
    case FLIPPED:
        Drawer::flippedOrientationDraw(pic, g, pos);
        break;
    case LEFT:
        Drawer::leftOrientationDraw(pic, g, pos);
        break;
    }
}

void Drawer::drawMask(Picture &pic, Picture &mask, Vec2 maskStart,
                      SDL_Plotter &g, Vec2 pos, Orientation orient) {
    assert(maskStart.x + mask.width <= pic.width);
    assert(maskStart.y + mask.height <= pic.height);
    switch (orient) {
    case NORMAL:
        Drawer::topOrientationMask(pic, mask, maskStart, g, pos, orient);
        break;
    case RIGHT:
        Drawer::rightOrientationMask(pic, mask, maskStart, g, pos, orient);
        break;
    case FLIPPED:
        Drawer::flippedOrientationMask(pic, mask, maskStart, g, pos, orient);
        break;
    case LEFT:
        Drawer::leftOrientationMask(pic, mask, maskStart, g, pos, orient);
        break;
    }
}

void Drawer::topOrientationDraw(Picture &pic, SDL_Plotter &g, Vec2 pos) {
    for (int i = 0; i < pic.height; i++) {
        for (int j = 0; j < pic.width; j++) {
            color pixel = pic.picData[i][j];
            g.plotPixel(pos.x + j, pos.y + i, pixel.R, pixel.G, pixel.B);
        }
    }
}

void Drawer::rightOrientationDraw(Picture &pic, SDL_Plotter &g, Vec2 pos) {
    pos += pic.dim().flip();
    for (int i = 0; i < pic.height; i++) {
        for (int j = 0; j < pic.width; j++) {
            color pixel = pic.picData[i][j];
            g.plotPixel(pos.x - i, pos.y - j, pixel.R, pixel.G, pixel.B);
        }
    }
}

void Drawer::flippedOrientationDraw(Picture &pic, SDL_Plotter &g, Vec2 pos) {
    pos += pic.dim();
    for (int i = 0; i < pic.height; i++) {
        for (int j = 0; j < pic.width; j++) {
            color pixel = pic.picData[i][j];
            g.plotPixel(pos.x - j, pos.y - i, pixel.R, pixel.G, pixel.B);
        }
    }
}
void Drawer::leftOrientationDraw(Picture &pic, SDL_Plotter &g, Vec2 pos) {
    for (int i = 0; i < pic.height; i++) {
        for (int j = 0; j < pic.width; j++) {
            color pixel = pic.picData[i][j];
            g.plotPixel(pos.x + i, pos.y + j, pixel.R, pixel.G, pixel.B);
        }
    }
}
void Drawer::topOrientationMask(Picture &pic, Picture &mask, Vec2 maskStart,
                                SDL_Plotter &g, Vec2 pos, Orientation orient) {
    iVec2 start = maskStart.toIVec2();
    for (int i = 0; i < mask.height; i++) {
        for (int j = 0; j < mask.width; j++) {
            color pixel = pic.picData[i + start.x][j + start.y];
            color maskPixel = mask.getPixel(i, j);
            if (maskPixel.R != 0 && maskPixel.G != 0 && maskPixel.B != 0) {
                g.plotPixel(pos.x + j, pos.y + i, pixel.R, pixel.G, pixel.B);
            }
        }
    }
}
void Drawer::rightOrientationMask(Picture &pic, Picture &mask, Vec2 maskStart,
                                  SDL_Plotter &g, Vec2 pos,
                                  Orientation orient) {
    iVec2 start = maskStart.toIVec2();
    pos += mask.dim().flip();
    for (int i = 0; i < mask.height; i++) {
        for (int j = 0; j < mask.width; j++) {
            color pixel = pic.picData[i + start.x][j + start.y];
            color maskPixel = mask.getPixel(i, j);
            if (maskPixel.R != 0 && maskPixel.G != 0 && maskPixel.B != 0) {
                g.plotPixel(pos.x - i, pos.y - j, pixel.R, pixel.G, pixel.B);
            }
        }
    }
}
void Drawer::flippedOrientationMask(Picture &pic, Picture &mask, Vec2 maskStart,
                                    SDL_Plotter &g, Vec2 pos,
                                    Orientation orient) {
    iVec2 start = maskStart.toIVec2();
    pos += mask.dim();
    for (int i = 0; i < mask.height; i++) {
        for (int j = 0; j < mask.width; j++) {
            color pixel = pic.picData[i + start.x][j + start.y];
            color maskPixel = mask.getPixel(i, j);
            if (maskPixel.R != 0 && maskPixel.G != 0 && maskPixel.B != 0) {
                g.plotPixel(pos.x - j, pos.y - i, pixel.R, pixel.G, pixel.B);
            }
        }
    }
}
void Drawer::leftOrientationMask(Picture &pic, Picture &mask, Vec2 maskStart,
                                 SDL_Plotter &g, Vec2 pos, Orientation orient) {
    iVec2 start = maskStart.toIVec2();
    for (int i = 0; i < mask.height; i++) {
        for (int j = 0; j < mask.width; j++) {
            color pixel = pic.picData[i + start.x][j + start.y];
            color maskPixel = mask.getPixel(i, j);
            if (maskPixel.R != 0 && maskPixel.G != 0 && maskPixel.B != 0) {
                g.plotPixel(pos.x + i, pos.y + j, pixel.R, pixel.G, pixel.B);
            }
        }
    }
}
