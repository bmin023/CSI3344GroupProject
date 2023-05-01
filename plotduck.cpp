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
void testSnappable(Piece &piece, Drawer &drawer);

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
    point offset;
    Typer t;

    while (!window.getQuit()) {
        while (state == TITLE && !window.getQuit()) {
            t.Write("EPIC PUZZLE GAME", window, Vec2(100, 160), color(0, 0, 0),
                    5, false);
            t.Write("Djisktras Disciples", window, Vec2(100, 220),
                    color(0, 0, 0), 3, false);
            t.Write("Click to begin", window, Vec2(100, 300), color(255, 0, 0),
                    7, false);
            if (window.mouseClick()) {
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
        if (selectedPiece != nullptr) {
            // cout << selectedPiece->thing << endl;
            point p;
            window.getMouseLocation(p.x, p.y);
            p.x -= offset.x;
            p.y -= offset.y;
            movePiece(*selectedPiece, p, drawer);
        }
        puzzle.draw(drawer);
        if (window.mouseClick()) {
            // cout << "mouse click" << endl;
            point click = window.getMouseClick();
            if (selectedPiece != nullptr) {
                testSnappable(*selectedPiece, drawer);
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
        window.update();
    }
    return 0;
}

void testSnappable(Piece &piece, Drawer &drawer) {
    // cout << " -- test -- " << endl;
    // cout << "NORMAL";
    int moved = false;
    if (piece.isSnappable(NORMAL)) {
        // cout << " was GOOD" << endl;
        movePiece(piece, piece.snap(NORMAL).toPoint(), drawer);
        moved = true;
        piece.connect(NORMAL);
    } else {
        // cout << " was BAD" << endl;
    }
    // cout << "RIGHT";
    if (piece.isSnappable(RIGHT)) {
        // cout << " was GOOD" << endl;
        if (!moved) {
            movePiece(piece, piece.snap(RIGHT).toPoint(), drawer);
            moved = true;
        }
        piece.connect(RIGHT);
    } else {
        // cout << " was BAD" << endl;
    }
    // cout << "FLIPPED";
    if (piece.isSnappable(FLIPPED)) {
        // cout << " was GOOD" << endl;
        if (!moved) {
            movePiece(piece, piece.snap(FLIPPED).toPoint(), drawer);
            moved = true;
        }
        piece.connect(FLIPPED);
    } else {
        // cout << " was BAD" << endl;
    }
    // cout << "LEFT";
    if (piece.isSnappable(LEFT)) {
        // cout << " was GOOD" << endl;
        if (!moved) {
            movePiece(piece, piece.snap(LEFT).toPoint(), drawer);
            moved = true;
        }
        piece.connect(LEFT);
    } else {
        // cout << " was BAD" << endl;
    }
    // cout << " -- end test -- " << endl << endl;
    cout << piece.getConnected() << endl;
}

void movePiece(Piece &selectedPiece, point p, Drawer &drawer) {
    Background bg = Background();
    selectedPiece.move(Vec2::fromPoint(p), drawer, bg);
    selectedPiece.setMoved(false);
}
