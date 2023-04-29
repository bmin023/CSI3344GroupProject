#include "superPiece.h"

void SuperPiece::move(Vec2 newPos){
    Vec2 offset = newPos - pos;
    for(int i = 0; i < pieces.size(); i++){
        pieces[i]->setPos(pieces[i]->getPos() + offset);
    }
    pos = newPos;
}

void SuperPiece::eat(SuperPiece& other){
    for(int i = 0; i < other.pieces.size(); i++){
        pieces.push_back(other.pieces[i]);
    }
    other.pieces.clear();
}

bool SuperPiece::snap(){
    
    return true;
}