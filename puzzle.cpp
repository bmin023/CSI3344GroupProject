/* Author: Brendon Kofink
 *         Wesley Goyette
 *         Aaron Sierra
 *         David Day
 *         Lucy Ray
 * Assignment Title: Epicer Puzzle
 * Assignment Description: A Puzzle game where the user can
 *   solve a puzzle by moving and snapping pieces into place.
 * Due Date: 5/4/2023
 * Date Created: 4/20/2023
 * Date Last Modified: 4/20/2023
 */
#include "puzzle.h"
#include "SDL_Plotter.h"
#include "picture.h"

Puzzle::Puzzle(string filename, int maxHeight, int maxWidth) {
    this->picture = Picture(filename);
    this->numAcross = picture.getWidth() / 96;
    this->numDown = picture.getHeight() / 96;

    this->pieceTable = new Piece **[numDown];
    for (int i = 0; i < numDown; i++) {
        this->pieceTable[i] = new Piece *[numAcross];
    }

    Vec2 imgOffStart = Vec2(0, 0); // remember it is (y, x)! (Only for accessing
                                   // the picture. Piece coordinates are (x, y))
    Vec2 posOnScreen = Vec2(20, 20);
    srand(time(NULL));

    for (int i = 0; i < numDown; i++) {
        for (int j = 0; j < numAcross; j++) {
            imgOffStart = Vec2(j * 96, i * 96);
            posOnScreen = Vec2(rand() % (maxWidth - 256), rand() % (maxHeight - 256));
            pieceTable[i][j] = new Piece(&picture, imgOffStart, posOnScreen);
            bool flip = false;
            Picture *edge = edgeLoader.getRandomEdge(flip);
            Edge norm = Edge(*edge, flip);
            Edge inv = Edge(*edge, !flip);

            if (j > 0) {
                pieceTable[i][j]->setNeighbor(
                    Orientation::LEFT,
                    pieceTable[i][j - 1]); // left neighbor assignment
                pieceTable[i][j]->setEdge(Orientation::LEFT,
                                          norm); // left edge assignment

                pieceTable[i][j - 1]->setNeighbor(
                    Orientation::RIGHT,
                    pieceTable[i][j]); // right neighbor assignment
                pieceTable[i][j - 1]->setEdge(Orientation::RIGHT,
                                              inv); // right edge assignment
            }

            if (i > 0) {
                pieceTable[i][j]->setNeighbor(
                    Orientation::NORMAL,
                    pieceTable[i - 1][j]); // top neighbor assignment
                pieceTable[i][j]->setEdge(Orientation::NORMAL,
                                          norm); // top edge assignment
                pieceTable[i - 1][j]->setNeighbor(
                    Orientation::FLIPPED,
                    pieceTable[i][j]); // bottom neighbor assignment
                pieceTable[i - 1][j]->setEdge(Orientation::FLIPPED,
                                              inv); // bottom edge assignment
            }
        }
    }
}

Puzzle::Puzzle(const Puzzle &other) {
    this->numAcross = other.numAcross;
    this->numDown = other.numDown;
    this->picture = other.picture;
    this->edgeLoader = other.edgeLoader;
    pieceTable = new Piece **[numDown];
    for (int i = 0; i < numDown; i++) {
        pieceTable[i] = new Piece *[numAcross];
        for (int j = 0; j < numAcross; j++) {
            pieceTable[i][j] = new Piece(*other.pieceTable[i][j]);
            if (j > 0) {
                pieceTable[i][j]->setNeighbor(
                    Orientation::LEFT,
                    pieceTable[i][j - 1]); // left neighbor assignment

                pieceTable[i][j - 1]->setNeighbor(
                    Orientation::RIGHT,
                    pieceTable[i][j]); // right neighbor assignment
            }
            if (i > 0) {
                pieceTable[i][j]->setNeighbor(
                    Orientation::NORMAL,
                    pieceTable[i - 1][j]); // top neighbor assignment
                pieceTable[i - 1][j]->setNeighbor(
                    Orientation::FLIPPED,
                    pieceTable[i][j]); // bottom neighbor assignment
            }
        }
    }
}

Puzzle::Puzzle(Puzzle&& other) {
    picture = other.picture;
    pieceTable = other.pieceTable;
    other.pieceTable = nullptr;
    numAcross = other.numAcross;
    other.numAcross = 0;
    numDown = other.numDown;
    other.numDown = 0;
    edgeLoader = other.edgeLoader;
}

Puzzle& Puzzle::operator=(Puzzle &&other) {
    if(this != &other) {
        if(pieceTable != nullptr) {
            for (int i = 0; i < numDown; i++) {
                for (int j = 0; j < numAcross; j++) {
                    delete pieceTable[i][j];
                }
                delete[] pieceTable[i];
            }
            delete[] pieceTable;
        }
        picture = std::move(other.picture);
        pieceTable = other.pieceTable;
        other.pieceTable = nullptr;
        numAcross = other.numAcross;
        other.numAcross = 0;
        numDown = other.numDown;
        other.numDown = 0;
        edgeLoader = std::move(other.edgeLoader);
        
        for(int i = 0; i < numDown; i++) {
            for(int j = 0; j < numAcross; j++) {
                pieceTable[i][j]->image = &picture;
            }
        }
    }
    return *this;
}

Puzzle &Puzzle::operator=(const Puzzle &other) {
    if (this != &other) {
        this->numAcross = other.numAcross;
        this->numDown = other.numDown;
        this->picture = other.picture;
        this->edgeLoader = other.edgeLoader;
        pieceTable = new Piece **[numDown];
        for (int i = 0; i < numDown; i++) {
            pieceTable[i] = new Piece *[numAcross];
            for (int j = 0; j < numAcross; j++) {
                pieceTable[i][j] = new Piece(*other.pieceTable[i][j]);
                if (j > 0) {
                    pieceTable[i][j]->setNeighbor(
                        Orientation::LEFT,
                        pieceTable[i][j - 1]); // left neighbor assignment

                    pieceTable[i][j - 1]->setNeighbor(
                        Orientation::RIGHT,
                        pieceTable[i][j]); // right neighbor assignment
                }
                if (i > 0) {
                    pieceTable[i][j]->setNeighbor(
                        Orientation::NORMAL,
                        pieceTable[i - 1][j]); // top neighbor assignment
                    pieceTable[i - 1][j]->setNeighbor(
                        Orientation::FLIPPED,
                        pieceTable[i][j]); // bottom neighbor assignment
                }
            }
        }
    }
    return *this;
}

Puzzle::~Puzzle() {
    for (int i = 0; i < numDown; i++) {
        for (int j = 0; j < numAcross; j++) {
            delete pieceTable[i][j];
        }
        delete[] pieceTable[i];
    }
    delete[] pieceTable;
}

void Puzzle::draw(Drawer &drawer) {
    for (int i = 0; i < numDown; i++) {
        for (int j = 0; j < numAcross; j++) {
            pieceTable[i][j]->draw(drawer);
        }
    }
}

/*
 *       TitleOfFunction: mouseClick
 *  Description:    This will check to see if the mouse has clicked on a
 * piece return:         bool - true if a piece was clicked on, false
 * otherwise precondition:   there are puzzles on the screen post-condition:
 * nothing is changed after click
 *
 */
bool Puzzle::mouseClick(point p, Piece **selectedPiece) {

    // this bool variable will be useful in the event we need to debug
    bool pieceClickedOn = false;
    // linear search below, this is fine because there will not be many
    // pieces
    for (int i = numDown - 1; i >= 0; i--) {
        for (int j = numAcross - 1; j >= 0; j--) {
            // call the isClicked function from piece
            if (pieceTable[i][j]->isClicked(p)) {
                *selectedPiece = pieceTable[i][j];
                pieceClickedOn = true;
                return pieceClickedOn;
            }
        }
    }

    return pieceClickedOn;
}
