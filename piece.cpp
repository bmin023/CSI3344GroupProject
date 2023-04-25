#include "piece.h"
#include "picture.h"

// Intentional Shallow Copy.
Edge::Edge(Picture &pic, bool inverted) : Picture() {
    this->inverted = inverted;
    width = pic.width;
    height = pic.height;
    picData = pic.picData;
    cout << height << endl;
    cout << width << endl;
}

Edge::~Edge() { cout << "edge delete" << endl; }

color Edge::getPixel(int x, int y) {
    color col;
    if (picData == nullptr) {
        if (y < height / 2) {
            col = color(0, 0, 0);
        } else {
            col = color(255, 255, 255);
        }
    } else {
        if (x + y < height - 1) {
            col = color(0, 0, 0);
            return col;
        }
        if (x - y >= width - height || x + y >= width) {
            col = color(0, 0, 0);
            return col;
        }
        if (inverted) {
            x = height - x - 1;
        }
        col = picData[x][y];
    }
    if (inverted) {
        col.R = 255 - col.R;
        col.G = 255 - col.G;
        col.B = 255 - col.B;
    }
    return col;
}

Edge Edge::operator=(const Edge &other) {
    cout << "edge copy" << endl;
    picData = other.picData;
    width = other.width;
    height = other.height;
    inverted = other.inverted;
    cout << "edge copy done" << endl;
    return *this;
}

Edge::Edge() : Picture() {
    cout << "make" << endl;
    width = 128;
    height = 32;
    picData = nullptr;
    cout << "done" << endl;
}

Piece::Piece(Picture &image, Vec2 imagePos, Vec2 pos)
    : image(image), imagePos(imagePos), pos(pos), topEdge(), bottomEdge(),
      lEdge(), rEdge() {
    orientation = NORMAL;
}

void Piece::draw(Drawer &drawer) {
    Vec2 pictureDim = Vec2(128, 128);
    Vec2 edgedim = Vec2(128, 32);
    Vec2 unitVec = Vec2(1, 1);
    drawer.drawMask(image, topEdge, imagePos, pos);
    drawer.drawMask(
        image, bottomEdge, imagePos + pictureDim.ycomp() - edgedim.ycomp(),
        pos + pictureDim.ycomp() - edgedim.ycomp(), Orientation::FLIPPED);
    drawer.drawMask(image, lEdge, imagePos, pos, Orientation::LEFT);
    drawer.drawMask(
        image, rEdge, imagePos + edgedim.xcomp() - edgedim.ycomp().flip(),
        pos + edgedim.xcomp() - edgedim.ycomp().flip(), Orientation::RIGHT);
    drawer.drawPart(image, imagePos + edgedim.splaty(),
                    pictureDim - edgedim.splaty() * 2 + UNIT,
                    pos + edgedim.splaty(), Orientation::NORMAL);
}
