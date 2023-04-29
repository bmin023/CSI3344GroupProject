#include <iostream>
#include <cmath>
#include <fstream>
#include "SDL_Plotter.h"
#include "picture.h"
#include "piece.h"
#include "puzzle.h"
#include "vec2.h"
#include <string>

using namespace std;

void movePiece(Piece& piece, point p, Drawer& drawer);
void testSnappable(Piece& piece, Drawer& drawer);

int main(int argc, char ** argv){
    string colorPNG = "./picturetxts/colors.jpg.txt";
    Piece* selectedPiece = nullptr;
    SDL_Plotter window (1000, 1000, true);
    Drawer drawer = Drawer(window);
    Puzzle puzzle = Puzzle(colorPNG);
    point offset;

    while(!window.getQuit()){
        if(selectedPiece != nullptr){
            // cout << selectedPiece->thing << endl;
            point p;
            window.getMouseLocation(p.x, p.y);
            p.x -= offset.x;
            p.y -= offset.y;
            movePiece(*selectedPiece, p, drawer);
        }
        puzzle.draw(drawer);
        if(window.mouseClick()){
            // cout << "mouse click" << endl;
            point click = window.getMouseClick();
            if(selectedPiece != nullptr) {
                testSnappable(*selectedPiece, drawer);
                selectedPiece = nullptr;
            } else if(puzzle.mouseClick(click, &selectedPiece)){
                // cout << "piece clicked on" << endl;
                offset.x = click.x - selectedPiece->getPos().x;
                offset.y = click.y - selectedPiece->getPos().y;
                //verifying cout statement for mouse click
            } //check for mouse click on puzzle
            while(window.mouseClick()){
                window.getMouseClick();
            }
        }
        window.update();
    }
    return 0;
}

void testSnappable(Piece& piece, Drawer& drawer) {
    cout << " -- test -- " << endl;
    cout << "NORMAL";
    if(piece.isSnappable(NORMAL)) {
        cout << " was GOOD" << endl;
        movePiece(piece,piece.snap(NORMAL).toPoint(),drawer);
    }
    else{
        cout << " was BAD" << endl;
    }
    cout << "RIGHT";
    if(piece.isSnappable(RIGHT)) {
        cout << " was GOOD" << endl;
        movePiece(piece,piece.snap(RIGHT).toPoint(),drawer);
    }else{
        cout << " was BAD" << endl;
    }
    cout << "FLIPPED";
    if(piece.isSnappable(FLIPPED)) {
        cout << " was GOOD" << endl;
        piece.snap(FLIPPED);
        movePiece(piece,piece.snap(FLIPPED).toPoint(),drawer);
    }else{
        cout << " was BAD" << endl;
    }
    cout << "LEFT";
    if(piece.isSnappable(LEFT)) {
        cout << " was GOOD" << endl;
        movePiece(piece,piece.snap(LEFT).toPoint(),drawer);
    }else{
        cout << " was BAD" << endl;
    }
    cout << " -- end test -- " << endl << endl;
}


void movePiece(Piece& selectedPiece, point p, Drawer& drawer){
    int x = p.x, y = p.y;
    Vec2 newPos(x,y);
    Background bg = Background();
    selectedPiece.draw(drawer, bg);
    selectedPiece.setPos(newPos);
}
