#include <iostream>
#include <cmath>
#include <fstream>
#include "SDL_Plotter.h"
#include "picture.h"
#include "piece.h"
#include "puzzle.h"
#include "Typer.h"
#include "vec2.h"
#include <string>

using namespace std;

void movePiece(Piece& piece, point p, Drawer& drawer);

int main(int argc, char ** argv){
    enum gameState
    {
        TITLE,
        PLAY,
        WIN,
    };
    gameState state = TITLE;

    string colorPNG = "./picturetxts/colors.jpg.txt";
    Piece* selectedPiece = nullptr;
    SDL_Plotter window (1000, 1000, true);
    Drawer drawer = Drawer(window);
    Puzzle puzzle = Puzzle(colorPNG);
    point offset;
    Typer t;

    while(!window.getQuit()){
        while(state == TITLE && !window.getQuit()){
            t.Write("EPIC PUZZLE GAME", window, Vec2(100, 160), color(0,0,0), 5, false);
            t.Write("Djisktras Disciples", window, Vec2(100, 220), color(0,0,0), 3, false);
            t.Write("Click to begin", window, Vec2(100, 300), color(255,0,0), 7, false);
            if (window.mouseClick()){
                state = PLAY;  //if space is hit, game is in PLAY state
                t.Write("EPIC PUZZLE GAME", window, Vec2(100, 160), color(255,255,255), 5, false); 
                t.Write("Djisktras Disciples", window, Vec2(100, 220), color(255,255,255), 3, false);     
                t.Write("Click to begin", window, Vec2(100, 300), color(255,255,255), 7, false);      
            }
            window.update();
        }
        if(selectedPiece != nullptr){
            // cout << selectedPiece->thing << endl;
            point p;
            window.getMouseLocation(p.x, p.y);
            p.x -= offset.x;
            p.y -= offset.y;
            movePiece(*selectedPiece, p, drawer);
        }
        puzzle.draw(drawer);
        if(window.mouseClick()){
            cout << "mouse click" << endl;
            point click = window.getMouseClick();
            if(selectedPiece != nullptr) {
                selectedPiece = nullptr;
            } else if(puzzle.mouseClick(click, &selectedPiece)){
                cout << "piece clicked on" << endl;
                offset.x = click.x - selectedPiece->getPos().x;
                offset.y = click.y - selectedPiece->getPos().y;
                //verifying cout statement for mouse click
            } //check for mouse click on puzzle
            while(window.mouseClick()){
                window.getMouseClick();
            }
        }
        window.update();
    }
    return 0;
}


void movePiece(Piece& selectedPiece, point p, Drawer& drawer){
    int x = p.x, y = p.y;
    Vec2 newPos(x,y);
    Background bg = Background();
    selectedPiece.draw(drawer, bg);
    selectedPiece.setPos(newPos);
}
