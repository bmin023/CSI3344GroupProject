#include "piece.h"
#include "picture.h"

// Intentional Shallow Copy.
Edge::Edge(Picture &pic, bool inverted) : Picture() {
    this->inverted = inverted;
    width = pic.width;
    height = pic.height;
    picData = pic.picData;
    this->owner = false;
}

Edge::~Edge() { owner = false; }

color Edge::getPixel(int x, int y) {
    color col;
    if (picData == nullptr) {
        int abs = (x - height / 2);
        // if (abs < 0) {
        //     abs = -abs;
        // }
        if (y < abs + height / 2) {
            return color(255, 0, 0);
        }
        if (y > -abs + width - height / 2) {
            col = color(0, 255, 0);
            return col;
        }
        if (x < height/2 || y < height/2 || y > width - height/2) {
            col = color(0, 0, 0);
        } else {
            col = color(255, 255, 255);
        }
        return col;
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
        if(y + x == height - 1) {
            col = color(0, 0, 255);
            return col;
        }
        if(y - x == width - height) {
            col = color(0, 0, 255);
            return col;
        }
        if (inverted) {
            x = height - x;
            y = width - y;
            if(x >= height || x+y == width) {
                return color(0, 0, 0);
            }
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
    inverted = false;
}

Piece::Piece(Picture &image, Vec2 imagePos, Vec2 pos)
    : image(image), imagePos(imagePos), pos(pos), topEdge(), bottomEdge(),
      lEdge(), rEdge() {
    orientation = NORMAL;
}

void Piece::draw(Drawer &drawer) { 
    draw(drawer, image); 
}
void Piece::draw(Drawer &drawer, Picture &pic) {
    Vec2 pictureDim = Vec2(128, 128);
    Vec2 edgedim = Vec2(128, 32);
    Vec2 unitVec = Vec2(1, 1);
    drawer.drawMask(pic, topEdge, imagePos, pos);
    drawer.drawMask(
        pic, bottomEdge, imagePos + pictureDim.ycomp() - edgedim.ycomp(),
        pos + pictureDim.ycomp() - edgedim.ycomp(), Orientation::FLIPPED);
    drawer.drawMask(pic, lEdge, imagePos, pos, Orientation::LEFT);
    drawer.drawMask(
        pic, rEdge, imagePos + edgedim.xcomp() - edgedim.ycomp().flip(),
        pos + edgedim.xcomp() - edgedim.ycomp().flip(), Orientation::RIGHT);
    drawer.drawPart(pic, imagePos + edgedim.splaty(),
                    pictureDim - edgedim.splaty() * 2 + UNIT,
                    pos + edgedim.splaty(), Orientation::NORMAL);
}

void Piece::setNeighbor(int index, Piece* neighbor){
    this->neighborArr[index] = neighbor;
}

/*
*       isClicked
*  Description:    This function checks to see if the piece has been clicked on
*                  by checking to see if the point falls within the bounds of
*                  the given piece.
*  return:         bool - true if the piece has been clicked on, false otherwise 
*  precondition:   there exists a piece object 
*  post-condition: nothing is changed 
*
*/
bool Piece::isClicked(point p) {
    //store the x and y values of the point
    int x = p.x, y = p.y;
        //this checks x values
    return x >= pos.x && x <= pos.x + 128 &&
        //this checks y values
        y >= pos.y && y <= pos.y + 128;
}

void Piece::setPos(const Vec2 &newPos){
    pos = newPos;
}

Vec2 Piece::getPos() const {
    return pos;
}

bool Piece::isSnappable(Orientation orient) {
    if(neighborArr[orient] == nullptr){
        return false;
    }
    Vec2 neighborPos = neighborArr[orient]->getPos();
    // cout << "sqmag " << (neighborPos - pos).sqMagnitude() << endl;
    if((neighborPos - pos).sqMagnitude() < 12000){
        // cout << "dot " << (neighborPos - pos).dot(orientations[orient]) << endl;
        if((neighborPos - pos).dot(orientations[orient]) > 0.3){
            return true;
        }
    }
    return false;
}

Vec2 Piece::snap(Orientation orient) {
    Piece* neighbor = neighborArr[orient];
    Vec2 neighborPos = neighbor->getPos();
    Vec2 newPos = neighborPos - orientations[orient] * 96;
    return newPos;
}
