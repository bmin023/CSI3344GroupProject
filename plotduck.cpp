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
    string sideBumpPNG = "./picturetxts/sidebump.png.txt";
    string dogPNG = "./picturetxts/dog.png.txt";
    Piece* selectedPiece;

    Picture duckPhoto = Picture(colorPNG);
    Picture mask = Picture(sideBumpPNG);
    Picture othermask = Picture(dogPNG);
    SDL_Plotter window (1000, 1000, true);
    Drawer drawer = Drawer(window);
    Puzzle puzzle = Puzzle(colorPNG);

    while(!window.getQuit()){
        if(window.mouseClick()){
            puzzle.draw(drawer);
            window.update();
            //check for mouse click on puzzle
            if(puzzle.mouseClick(window.getMouseClick(), selectedPiece)){
                //verifying cout statement for mouse click
                cout << "selectedPiece: " << &selectedPiece << endl;
                
            }
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
    othermask.dealloc();
    duckPhoto.dealloc();
    mask.dealloc();
    return 0;
}


 //bool movePiece(Piece& piece, Vec2& loc, Vc2& offset){
     
     
 //}
