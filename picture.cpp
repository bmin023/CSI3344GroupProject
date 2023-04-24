#include "picture.h"
#include "SDL_Plotter.h"

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
