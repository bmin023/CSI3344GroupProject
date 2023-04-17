#include "picture.h"

Picture::Picture(string filename){
    ifstream input;
    input.open(filename);
    if(!input){
        cerr << "ERROR COULD NOT OPEN FILE";
    }
    else{
        input >> this->height;
        input >> this->width;

        picData = new color*[height];
        for(int i = 0; i < height; i++){
            picData[i] = new color[width];
        }

        int R, G, B;
        for(int i = 0; i < height; i++){
            for(int j = 0; j < width; j++){
                if(input >> R >> G >> B){
                    //plotPixel(int x, int y, int r, int g, int b) - plots a single pixel at 
                    //location (x,y) and color (r,g,b)
                    color pixel;
                    pixel.R = R;
                    pixel.G = G;
                    pixel.B = B;

                    picData[i][j] = pixel;  
                }
            }
        }
        input.close();
    }
}

Picture::~Picture(){
    for(int i = 0; i < height; i++){
        delete[] picData[i];
    }

    delete[]picData;
}