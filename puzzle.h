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
        /*
         * description: constructor
         * return: none
         * precondition: The user wants to create a puzzle
         * postcondition: A puzzle is created with the given
         *  filename and dimensions
        */
        Puzzle(string filename, int maxHeight = 1000, int maxWidth = 1000);
        /*
         * description: Default Constructor cause some reason idk it needs one
         * return: none
         * precondition: The user wants to create a puzzle
         * postcondition: A puzzle is created with nothing.
        */
        Puzzle() {}
        /*
         * description: Copy Constructor
         * return: none
         * precondition: The user wants to create a puzzle
         * postcondition: A puzzle is created from another puzzle
        */
        Puzzle(const Puzzle& other);
        /*
         * description: Move Constructor
         * return: none
         * precondition: The user wants to create a puzzle
         * postcondition: A puzzle is created from another puzzle
        */
        Puzzle& operator=(Puzzle&& other);
        /*
         * description: Copy Assignment Operator
         * return: none
         * precondition: The user wants to create a puzzle
         * postcondition: A puzzle is created from another puzzle
        */
        Puzzle& operator=(const Puzzle& other);
        /*
         * description: Move Constructor
         * return: none
         * precondition: The user wants to create a puzzle
         * postcondition: A puzzle is created from another puzzle
        */
        Puzzle(Puzzle&& other);
        /*
         * description: Destructor
         * return: none
         * precondition: The user wants to delete a puzzle
         * postcondition: A puzzle is deleted
        */
        ~Puzzle();
        /*
         * description: draw the puzzle to the screen
         * return: none
         * precondition: The user wants to draw the puzzle
         * postcondition: The puzzle is drawn to the screen
        */
        void draw(Drawer &drawer);
        /*
         * description: gets the piece at the given point
         * return: bool
         * precondition: The user wants to get a piece
         * postcondition: selectedPiece is set to the piece at the given point
         * and true is returned if there is a piece at the given point
        */
        bool mouseClick(point p, Piece** selectedPiece);
        /*
         * description: the number of pieces in the puzzle
         * return: int
         * precondition: The user wants to know the number of pieces
         * postcondition: The number of pieces is returned
        */
        int pieces() {return numAcross * numDown;}
};
#endif //PUZZLE_H_INCLUDED
