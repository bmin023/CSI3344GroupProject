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

bool movePiece(Piece& piece, Vec2& loc, Vec2& offset);

int main(int argc, char ** argv){
    string colorPNG = "./picturetxts/colors.jpg.txt";
    SDL_Plotter window (1000, 1000, true);
    Drawer drawer = Drawer(window);
    Puzzle puzzle = Puzzle(colorPNG);

    while(!window.getQuit()){
        if(window.mouseClick()){
            puzzle.draw(drawer);
            window.update();
        }
        //if the puzzel piece is clicked on
        // if(/* Puzzel.mouseClick(window.getMouseClick()) */){
        //     /*
        //     window knows where the mouse click was, puzzle knows where
        //     all of its puzzle pieces are. We pass in the mouse click to puzzle
        //     object so it can check all of its members to see if the mouse click
        //     was on any of the puzzle pieces.
        //     
        //     */
        //
        //
        //    //now we call the move function if this was true
        //    //and we move until the window is clicked again
        // }
    }
    return 0;
}


// bool movePiece(Piece& piece, Vec2& loc, Vc2& offset){
//     
//     
// }
