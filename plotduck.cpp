#include <iostream>
#include <cmath>
#include <fstream>
#include "SDL_Plotter.h"
#include "picture.h"

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
    picture duckPhoto = picture("pixelduck.txt");
    SDL_Plotter window (duckPhoto.height, duckPhoto.width, true);

    while(!window.getQuit()){
        if(window.mouseClick()){
            for(int i = 0; i < duckPhoto.height; i++){
                for(int j = 0; j < duckPhoto.width; j++){
                    window.plotPixel(j, i, duckPhoto.picData[i][j]);
                }
            }
            window.update();
        }
    }

}