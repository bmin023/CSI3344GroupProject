#include "SDL_Plotter.h"
#include "Typer.h"
#include "picture.h"
#include "piece.h"
#include "puzzle.h"
#include "vec2.h"
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

void movePiece(Piece &piece, point p, Drawer &drawer);
bool testSnappable(Piece &piece, Drawer &drawer);

int main(int argc, char **argv) {
    enum gameState {
        TITLE,
        PLAY,
        WIN,
    };
    gameState state = TITLE;


    string colorPNG = "./picturetxts/colors.jpg.txt";
    Piece *selectedPiece = nullptr;
    SDL_Plotter window(1000, 1000, true);
    Drawer drawer = Drawer(window);
    Puzzle puzzle = Puzzle(colorPNG);
    cout << "onto the next thing." << endl;
    point offset;
    Typer t;

    window.initSound("Click.wav");
    window.initSound("GoodDesign.wav");
    window.initSound("NotUnderTale.wav");


    while (!window.getQuit()) {
        while (state == TITLE && !window.getQuit()) {
            t.Write("EPIC PUZZLE GAME", window, Vec2(100, 160), color(0, 0, 0),
                    5, false);
            t.Write("Djisktras Disciples", window, Vec2(100, 220),
                    color(0, 0, 0), 3, false);
            t.Write("Click to begin", window, Vec2(100, 300), color(255, 0, 0),
                    7, false);
            window.playSound("NotUnderTale.wav");
            if (window.mouseClick()) {
                window.quitSound("NotUnderTale.wav");
                state = PLAY; // if space is hit, game is in PLAY state
                t.Write("EPIC PUZZLE GAME", window, Vec2(100, 160),
                        color(255, 255, 255), 5, false);
                t.Write("Djisktras Disciples", window, Vec2(100, 220),
                        color(255, 255, 255), 3, false);
                t.Write("Click to begin", window, Vec2(100, 300),
                        color(255, 255, 255), 7, false);
            }
            window.update();
        }
        puzzle = Puzzle(colorPNG);
        if (window.mouseClick()) {
            window.getMouseClick();
        }
        while (state != TITLE && !window.getQuit()) {
            if (selectedPiece != nullptr) {
                // cout << selectedPiece->thing << endl;
                point p;
                window.getMouseLocation(p.x, p.y);
                p.x -= offset.x;
                p.y -= offset.y;
                movePiece(*selectedPiece, p, drawer);
            }
            if (window.mouseClick()) {
                // cout << "mouse click" << endl;
                point click = window.getMouseClick();
                if (selectedPiece != nullptr) {
                    if (testSnappable(*selectedPiece, drawer)) {
                        window.playSound("Click.wav");
                    }
                    if (state == PLAY && selectedPiece->getConnected() == puzzle.pieces()) {
                        state = WIN;
                        window.playSound("GoodDesign.wav");
                        if (window.kbhit()) {
                            window.getKey();
                        }
                    }
                    selectedPiece = nullptr;
                } else if (puzzle.mouseClick(click, &selectedPiece)) {
                    // cout << "piece clicked on" << endl;
                    offset.x = click.x - selectedPiece->getPos().x;
                    offset.y = click.y - selectedPiece->getPos().y;
                    // verifying cout statement for mouse click
                } // check for mouse click on puzzle
                while (window.mouseClick()) {
                    window.getMouseClick();
                }
            }
            puzzle.draw(drawer);

            if (state == WIN) {
                t.Write("You won", window, Vec2(100, 160), color(0, 0, 0), 10,
                        false);
                t.Write("press any key to play again", window, Vec2(100, 300),
                        color(255, 0, 0), 7, false);
                if (window.kbhit()) {
                    state = TITLE; // if space is hit, game is in PLAY state
                    window.clear();
                    // t.Write("You won", window, Vec2(100, 160), color(255,
                    // 255, 255), 10, false); t.Write("press any key to play
                    // again", window, Vec2(100, 300), color(255, 255, 255),7,
                    // false);
                }
            }

            window.update();
        }
    }
    return 0;
}

bool testSnappable(Piece &piece, Drawer &drawer) {
    int pieceNum = piece.getConnected();
    // cout << " -- test -- " << endl;
    // cout << "NORMAL";
    if (piece.isSnappable(NORMAL)) {
        // cout << " was GOOD" << endl;
        movePiece(piece, piece.snap(NORMAL).toPoint(), drawer);
        piece.connect(NORMAL);
    } else {
        // cout << " was BAD" << endl;
    }
    // cout << "RIGHT";
    if (piece.isSnappable(RIGHT)) {
        // cout << " was GOOD" << endl;
        movePiece(piece, piece.snap(RIGHT).toPoint(), drawer);
        piece.connect(RIGHT);
    } else {
        // cout << " was BAD" << endl;
    }
    // cout << "FLIPPED";
    if (piece.isSnappable(FLIPPED)) {
        // cout << " was GOOD" << endl;
        movePiece(piece, piece.snap(FLIPPED).toPoint(), drawer);
        piece.connect(FLIPPED);
    } else {
        // cout << " was BAD" << endl;
    }
    // cout << "LEFT";
    if (piece.isSnappable(LEFT)) {
        // cout << " was GOOD" << endl;
        movePiece(piece, piece.snap(LEFT).toPoint(), drawer);
        piece.connect(LEFT);
    } else {
        // cout << " was BAD" << endl;
    }
    // cout << " -- end test -- " << endl << endl;
    cout << piece.getConnected() << endl;
    return piece.getConnected() > pieceNum;
}

void movePiece(Piece &selectedPiece, point p, Drawer &drawer) {
    Background bg = Background();
    selectedPiece.move(Vec2::fromPoint(p), drawer, bg);
    selectedPiece.setMoved(false);
}
