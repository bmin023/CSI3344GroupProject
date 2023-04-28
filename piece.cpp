#include "piece.h"
#include "picture.h"

// Intentional Shallow Copy.
Edge::Edge(Picture &pic, bool inverted) : Picture() {
    this->inverted = inverted;
    width = pic.width;
    height = pic.height;
    picData = pic.picData;
}

Edge::~Edge() {}

color Edge::getPixel(int x, int y) {
    color col;
    if (picData == nullptr) {
        if (x < height/2 || y < height/2 || y > width - height/2) {
            col = color(0, 0, 0);
        } else {
            col = color(255, 255, 255);
        }
    } else {
        int abs = (x - height / 2);
        if (abs < 0) {
            abs = -abs;
        }
        if (y < abs + height / 2) {
            return color(255, 0, 0);
        }
        if (y > -abs + width - height / 2) {
            col = color(0, 255, 0);
            return col;
        }
        if (inverted) {
            x = height - x - 1;
            y = width - y - 1;
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
    picData = other.picData;
    width = other.width;
    height = other.height;
    inverted = other.inverted;
    return *this;
}

Edge::Edge() : Picture() {
    width = 128;
    height = 32;
    picData = nullptr;
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

void Piece::setNeighbor(int index, Piece* neighbor){
    this->neighborArr[index] = neighbor;
}
