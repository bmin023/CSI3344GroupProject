#include <iostream>
#include <cmath>
#include <fstream>
#include "SDL_Plotter.h"
#include "picture.h"
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
    Picture duckPhoto = Picture("pixelduck.txt");
    Picture mask = Picture("biggump.png.txt");
    SDL_Plotter window (1000, 1000, true);

    while(!window.getQuit()){
        if(window.mouseClick()){
            Vec2 pos = Vec2(0,0);
            Drawer::drawMask(duckPhoto, mask, Vec2(0,0), window, pos, Orientation::RIGHT);
            // Drawer::drawPicture(mask, window, pos);
            window.update();
        }
    }

}
