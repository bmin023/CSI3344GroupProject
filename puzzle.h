/* Author: Brendon Kofink
 *         Wesley Goyette
 *         Aaron Sierra
 *         David Day
 *         Lucy Ray
 * Assignment Title: Epicer Puzzle
 * Assignment Description: A Puzzle game where the user can
 *   solve a puzzle by moving and snapping pieces into place.
 * Due Date: 5/4/2023
 * Date Created: 4/20/2023
 * Date Last Modified: 4/20/2023
 */
#ifndef PUZZLE_H_INCLUDED
#define PUZZLE_H_INCLUDED

#include <iostream>
#include "edgeloader.h"
#include "piece.h"
#include "picture.h"

class Puzzle{
    private: 
        Picture picture;
        Piece*** pieceTable = nullptr; //2d array of piece pointers
        EdgeLoader edgeLoader;
        int numAcross;
        int numDown;
     public:
        Puzzle(string filename, int maxHeight = 1000, int maxWidth = 1000);
        Puzzle() {}
        Puzzle(const Puzzle& other);
        Puzzle& operator=(Puzzle&& other);
        Puzzle& operator=(const Puzzle& other);
        Puzzle(Puzzle&& other);
        ~Puzzle();
        void draw(Drawer &drawer);
        //window.mouseClick()
        bool mouseClick(point p, Piece** selectedPiece);
        int pieces() {return numAcross * numDown;}
};
#endif //PUZZLE_H_INCLUDED
