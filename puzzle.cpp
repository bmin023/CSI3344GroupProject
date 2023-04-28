#include "puzzle.h"
#include "SDL_Plotter.h"
#include "picture.h"

Puzzle::Puzzle(string filename) {
    this->picture = new Picture(filename);
    cout << "picture width: " << picture->getWidth() << endl;
    cout << "picture height: " << picture->getHeight() << endl;
    this->numAcross = picture->getWidth() / 96;
    this->numDown = picture->getHeight() / 96;
    cout << "numAcross: " << numAcross << endl;
    cout << "numDown: " << numDown << endl;

    this->pieceTable = new Piece **[numDown];
    for (int i = 0; i < numDown; i++) {
        this->pieceTable[i] = new Piece *[numAcross];
    }

    Vec2 imgOffStart = Vec2(0, 0); // remember it is (y, x)! (Only for accessing
                                   // the picture. Piece coordinates are (x, y))
    Vec2 posOnScreen = Vec2(20, 20);

    for (int i = 0; i < numDown; i++) {
        for (int j = 0; j < numAcross; j++) {
            imgOffStart = Vec2(16 + j * 96, 16 + i * 96);
            posOnScreen = Vec2(j * 116, i * 116);
            pieceTable[i][j] = new Piece(*picture, imgOffStart, posOnScreen);
            bool flip = false;
            Picture *edge = edgeLoader.getRandomEdge(flip);
            Edge norm = Edge(*edge, flip);
            Edge inv = Edge(*edge, !flip);

            if (j > 0) {
                pieceTable[i][j]->setNeighbor(
                    Orientation::LEFT,
                    pieceTable[i][j - 1]); // left neighbor assignment
                pieceTable[i][j]->setEdge(
                    Orientation::LEFT,
                    norm); // left edge assignment

                pieceTable[i][j - 1]->setNeighbor(
                    Orientation::RIGHT,
                    pieceTable[i][j]); // right neighbor assignment
                pieceTable[i][j - 1]->setEdge(
                    Orientation::RIGHT,
                    inv); // right edge assignment
            }

            if (i > 0) {
                pieceTable[i][j]->setNeighbor(
                    Orientation::NORMAL,
                    pieceTable[i - 1][j]); // top neighbor assignment
                pieceTable[i][j]->setEdge(
                    Orientation::NORMAL,
                    norm); // top edge assignment
                pieceTable[i - 1][j]->setNeighbor(
                    Orientation::FLIPPED,
                    pieceTable[i][j]); // bottom neighbor assignment
                pieceTable[i - 1][j]->setEdge(
                    Orientation::FLIPPED,
                    inv); // bottom edge assignment
            }
        }
    }
}

Puzzle::~Puzzle() {
    for (int i = 0; i < numDown; i++) {
        for (int j = 0; j < numAcross; j++) {
            delete pieceTable[i][j];
        }
        delete[] pieceTable[i];
    }
    delete[] pieceTable;
    delete picture;
}

void Puzzle::draw(Drawer &drawer) {
    for (int i = 0; i < numDown; i++) {
        for (int j = 0; j < numAcross; j++) {
            pieceTable[i][j]->draw(drawer);
        }
    }
}

// bool Puzzle::mouseClick(point p){
// 	//return SDL_Plotter.click_queue.size() > 0;
//     //point SDL_Plotter::getMouseClick(){
// 	//point p;
//     //if(click_queue.size() > 0){
//     	//p = click_queue.front();
//     	//click_queue.pop();
//     //}
//
// 	//return p;
//     SDL_Plotter.getMouseClick();
//
// }
