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
    Piece* selectedPiece;
    SDL_Plotter window (1000, 1000, true);
    Drawer drawer = Drawer(window);
    Puzzle puzzle = Puzzle(colorPNG);

    while(!window.getQuit()){
        if(window.mouseClick()){
            puzzle.draw(drawer);
            window.update();
            //check for mouse click on puzzle
            if(puzzle.mouseClick(window.getMouseClick(), &selectedPiece)){
                //verifying cout statement for mouse click
                while (selectedPiece != NULL){
                    point p;
                    window.getMouseLocation(p.x, p.y);
                    movePiece(*selectedPiece, p, drawer);
                    
                }
                
            }
        }
        
    }
    return 0;
}


void movePiece(Piece& selectedPiece, point p, Drawer& drawer){
    int x = p.x, y = p.y;
    Vec2 newPos(x,y);
    piece.setPos(newPos);
    piece.draw(drawer);
}
