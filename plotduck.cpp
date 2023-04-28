#include <iostream>
#include <cmath>
#include <fstream>
#include "SDL_Plotter.h"
#include "picture.h"
#include "piece.h"
#include "vec2.h"
#include <string>

using namespace std;

bool movePiece(Piece& piece, Vec2& loc, Vec2& offset);

int main(int argc, char ** argv){
    /*ifstream input;
    input.open("pixelduck.txt");
    if(!input){
        cout << "couldn't open file" << endl;
        return 1;
    }
    int r, c;
    input >> r;
    input >> c;
    cout << "r: " << r << " c: " << c << endl;*/
    string colorPNG = "./picturetxts/colors.jpg.txt";
    string sideBumpPNG = "./picturetxts/sidebump.png.txt";
    string dogPNG = "./picturetxts/dog.png.txt";

    Picture duckPhoto = Picture(colorPNG);
    Picture mask = Picture(sideBumpPNG);
    Picture othermask = Picture(dogPNG);
    SDL_Plotter window (1000, 1000, true);
    cout << "window created" << endl;
    Drawer drawer = Drawer(window);
    cout << "drawer created" << endl;
    Piece duck = Piece(duckPhoto, Vec2(0,0), Vec2(0,0));
    cout << "duck created" << endl;
    Edge invedge = Edge(mask,true);
    Edge edge = Edge(mask,false);
    Edge invbump = Edge(othermask,true);
    Edge bump = Edge(othermask,false);
    duck.setEdge(NORMAL, invedge);
    duck.setEdge(RIGHT, edge);
    duck.setEdge(FLIPPED, edge);
    duck.setEdge(LEFT, invedge);
    Piece other = Piece(duckPhoto, Vec2(96,0), Vec2(126,0));
    other.setEdge(NORMAL, invedge);
    other.setEdge(RIGHT, edge);
    other.setEdge(FLIPPED, edge);
    other.setEdge(LEFT, invedge);
    Piece third = Piece(duckPhoto, Vec2(0,96), Vec2(0,126));
    third.setEdge(NORMAL, invedge);
    third.setEdge(RIGHT, bump);
    third.setEdge(FLIPPED, invbump);
    third.setEdge(LEFT, bump);
    Piece fourth = Piece(duckPhoto, Vec2(96,96), Vec2(126,126));
    fourth.setEdge(NORMAL, invedge);
    fourth.setEdge(RIGHT, invbump);
    fourth.setEdge(FLIPPED, invbump);
    fourth.setEdge(LEFT, invbump);

    while(!window.getQuit()){
        if(window.mouseClick()){
            duck.draw(drawer);
            other.draw(drawer);
            third.draw(drawer);
            fourth.draw(drawer);
            // drawer.drawPicture(topEdge, Vec2(0,0));
            window.update();
        }
        //if the puzzel piece is clicked on
        if(/* Puzzel.mouseClick(window.getMouseClick()) */){
            /*
            window knows where the mouse click was, puzzle knows where
            all of its puzzle pieces are. We pass in the mouse click to puzzle
            object so it can check all of its members to see if the mouse click
            was on any of the puzzle pieces.
            
            */


           //now we call the move function if this was true
           //and we move until the window is clicked again
        }
    }
    duckPhoto.dealloc();
    mask.dealloc();
    return 0;
}


bool movePiece(Piece& piece, Vec2& loc, Vc2& offset){
    
    
}