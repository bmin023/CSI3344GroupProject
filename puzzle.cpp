#include "puzzle.h"
#include "SDL_Plotter.h"

Puzzle::Puzzle(string filename){
    this->picture = new Picture(filename);
    int numAcross = (picture->getWidth()-32)/96;
    int numDown = (picture->getHeight()-32)/96;

    this->pieceTable = new Piece**[numDown];
    for(int i = 0; i < numDown; i++){
        this->pieceTable[i] = new Piece*[numAcross];
    }

    Vec2 imgOffStart = Vec2(0, 0);  //remember it is (y, x)!
    Vec2 posOnScreen = Vec2(0,0);
    
    for(int i = 0; i < numDown; i++){
        for(int j = 0; j < numAcross; j++){
            pieceTable[i][j] = new Piece(*picture, imgOffStart, posOnScreen);
            imgOffStart = Vec2(i*96, j*96);
            posOnScreen = Vec2(i*96, j*96);

            if(j > 0){
                pieceTable[i][j]->setNeighbor(3, pieceTable[i][j-1]); //left neighbor assignment
                pieceTable[i][j-1]->setNeighbor(1, pieceTable[i][j]);  //right neighbor assignment
            }

            if(i > 0){
                pieceTable[i][j]->setNeighbor(0, pieceTable[i-1][j]);  //top neighbor assignment
                pieceTable[i-1][j]->setNeighbor(2, pieceTable[i][j]);  //bottom neighbor assignment
            }
        }
    }

    
}

bool Puzzle::mouseClick(point p){
	//return SDL_Plotter.click_queue.size() > 0;
    //point SDL_Plotter::getMouseClick(){
	//point p;
    //if(click_queue.size() > 0){
    	//p = click_queue.front();
    	//click_queue.pop();
    //}

	//return p;
    SDL_Plotter.getMouseClick();

}