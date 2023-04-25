#include <iostream>
#include <cmath>
#include <fstream>
#include "SDL_Plotter.h"
#include "picture.h"
#include "piece.h"
#include "vec2.h"

using namespace std;

int main(){
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
    Picture duckPhoto = Picture("colors.jpg.txt");
    Picture mask = Picture("sidebump.png.txt");
    SDL_Plotter window (1000, 1000, true);
    cout << "window created" << endl;
    Drawer drawer = Drawer(window);
    cout << "drawer created" << endl;
    Piece duck = Piece(duckPhoto, Vec2(0,0), Vec2(0,0));
    cout << "duck created" << endl;
    Edge invedge = Edge(mask,true);
    Edge edge = Edge(mask,false);
    duck.setEdge(NORMAL, invedge);
    duck.setEdge(RIGHT, edge);
    duck.setEdge(FLIPPED, edge);
    duck.setEdge(LEFT, invedge);
    cout << "edges set" << endl;

    while(!window.getQuit()){
        if(window.mouseClick()){
            duck.draw(drawer);
            // drawer.drawPicture(topEdge, Vec2(0,0));
            window.update();
        }
    }
    duckPhoto.dealloc();
    mask.dealloc();
    return 0;
}
