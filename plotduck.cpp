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
            cout << "mouse click" << endl;
            point click = window.getMouseClick();
            if(selectedPiece != nullptr) {
                selectedPiece = nullptr;
            } else if(puzzle.mouseClick(click, &selectedPiece)){
                cout << "piece clicked on" << endl;
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


void movePiece(Piece& selectedPiece, point p, Drawer& drawer){
    int x = p.x, y = p.y;
    Vec2 newPos(x,y);
    Background bg = Background();
    selectedPiece.draw(drawer, bg);
    selectedPiece.setPos(newPos);
}
