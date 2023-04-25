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

void Picture::dealloc() {
    cout << "picture delete" << endl;
    for (int i = 0; i < height; i++) {
        delete[] picData[i];
    }

    delete[] picData;
}

color Picture::getPixel(int x, int y) { return picData[x][y]; }

Vec2 Picture::dim() { return Vec2(width, height); }

void Drawer::drawPicture(Picture &pic, Vec2 pos, Orientation orient) {
    switch (orient) {
    case NORMAL:
        topOrientationDraw(pic, Vec2(0, 0), pic.dim(), pos, orient);
        break;
    case RIGHT:
        rightOrientationDraw(pic, Vec2(0, 0), pic.dim(), pos, orient);
        break;
    case FLIPPED:
        flippedOrientationDraw(pic, Vec2(0, 0), pic.dim(), pos, orient);
        break;
    case LEFT:
        leftOrientationDraw(pic, Vec2(0, 0), pic.dim(), pos, orient);
        break;
    }
}

void Drawer::drawPart(Picture &pic, Vec2 start, Vec2 dim, Vec2 pos,
              Orientation orient) {
    switch(orient) {
        case NORMAL:
            topOrientationDraw(pic, start, dim, pos, orient);
            break;
        case RIGHT:
            rightOrientationDraw(pic, start, dim, pos, orient);
            break;
        case FLIPPED:
            flippedOrientationDraw(pic, start, dim, pos, orient);
            break;
        case LEFT:
            leftOrientationDraw(pic, start, dim, pos, orient);
            break;
    }
}
void Drawer::drawMask(Picture &pic, Picture &mask, Vec2 maskStart, Vec2 pos,
                      Orientation orient) {
    assert(maskStart.x + mask.width <= pic.width);
    assert(maskStart.y + mask.height <= pic.height);
    switch (orient) {
    case NORMAL:
        topOrientationMask(pic, mask, maskStart, pos, orient);
        break;
    case RIGHT:
        rightOrientationMask(pic, mask, maskStart, pos, orient);
        break;
    case FLIPPED:
        flippedOrientationMask(pic, mask, maskStart, pos, orient);
        break;
    case LEFT:
        leftOrientationMask(pic, mask, maskStart, pos, orient);
        break;
    }
}

void Drawer::topOrientationDraw(Picture &pic, Vec2 start, Vec2 dim, Vec2 pos,
                                Orientation orient) {
    iVec2 iStart = start.toIVec2();
    for (int i = 0; i < dim.x; i++) {
        for (int j = 0; j < dim.y; j++) {
            color pixel = pic.picData[iStart.x + i][iStart.y + j];
            g.plotPixel(pos.x + j, pos.y + i, pixel.R, pixel.G, pixel.B);
        }
    }
}

void Drawer::rightOrientationDraw(Picture &pic, Vec2 start, Vec2 dim, Vec2 pos,
                                  Orientation orient) {
    iVec2 iStart = start.toIVec2();
    pos += pic.dim().flip();
    for (int i = 0; i < dim.x; i++) {
        for (int j = 0; j < dim.y; j++) {
            color pixel = pic.picData[iStart.x + i][iStart.y + j];
            g.plotPixel(pos.x - i, pos.y - j, pixel.R, pixel.G, pixel.B);
        }
    }
}

void Drawer::flippedOrientationDraw(Picture &pic, Vec2 start, Vec2 dim,
                                    Vec2 pos, Orientation orient) {
    iVec2 iStart = start.toIVec2();
    pos += pic.dim();
    for (int i = 0; i < dim.x; i++) {
        for (int j = 0; j < dim.y; j++) {
            color pixel = pic.picData[iStart.x + i][iStart.y + j];
            g.plotPixel(pos.x - j, pos.y - i, pixel.R, pixel.G, pixel.B);
        }
    }
}
void Drawer::leftOrientationDraw(Picture &pic, Vec2 start, Vec2 dim, Vec2 pos,
                                 Orientation orient) {
    iVec2 iStart = start.toIVec2();
    for (int i = 0; i < dim.x; i++) {
        for (int j = 0; j < dim.y; j++) {
            color pixel = pic.picData[iStart.x + i][iStart.y + j];
            g.plotPixel(pos.x + i, pos.y + j, pixel.R, pixel.G, pixel.B);
        }
    }
}
void Drawer::topOrientationMask(Picture &pic, Picture &mask, Vec2 maskStart,
                                Vec2 pos, Orientation orient) {
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
                                  Vec2 pos, Orientation orient) {
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
                                    Vec2 pos, Orientation orient) {
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
                                 Vec2 pos, Orientation orient) {
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
