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
#ifndef PIECE_H_INCLUDED
#define PIECE_H_INCLUDED

#include "SDL_Plotter.h"
#include "picture.h"
#include "vec2.h"

class Edge : public Picture {
    private:
        bool inverted;
    public:
        /*
        * description: default constructor for Edge    
        * return: none                                           
        * precondition: Picture object has been created with data from 
        *               PictureTXTs directory
        * postcondition: Edge object is constructed with the given picture data, 
        *                default is not inverted                                                       
        */
        Edge(Picture &pic, bool inverted = false);

        /*
        * description: default constructor for Edge    
        * return: none                                           
        * precondition: none                             
        * postcondition: default Edge object is constructed                                                       
        */
        Edge();

        /*
        * description: destructor    
        * return: none                                           
        * precondition: Edge object exists                             
        * postcondition: memory associated with Edge object is freed                                                       
        */
        ~Edge() override;

        /*
        * description: assignment operator overload    
        * return: Edge reference that is a copy of other                                           
        * precondition: Edge object other exists                             
        * postcondition: this is a copy of other                                                       
        */
        Edge& operator=(const Edge &other);

        /*
        * description: edge inversion calculator    
        * return: Color object representing white if it is meant to be drawn,
        *         any other color if it is not meant to be drawn                                           
        * precondition: an Edge object exists to find the inverse of
        * postcondition: the inversion of the edge pixel is calculated
        */
        color getPixel(int x, int y) override;
};

class Piece{
    private:
    bool moved = false;
    Vec2 imagePos;
    //neighbor array
    Piece* neighborArr [4] = {nullptr, nullptr, nullptr, nullptr};
    bool connected [4] = {false, false, false, false}; //connected array
    Orientation orientation;
    Edge topEdge, bottomEdge, lEdge, rEdge;
    Vec2 pos;

    /*
    * description: ping pieces to determine if they are connected
    * return: int number of pieces a piece is connected to                                           
    * precondition: none                           
    * postcondition: int number of pieces a piece is connected to is returned
    */
    int ping(int count);

    public:
    Picture* image;
    
    /*
    * description: Piece constructor
    * return: none
    * precondition: valid Picture and Vec2 parameters exist                           
    * postcondition: Piece is creaed with Picture pointer to image, an assigned
    *                portion of the image, and a position on screen
    */
    Piece(Picture *image, Vec2 imagePos, Vec2 pos);

    /*
    * description: Piece copy constructor
    * return: none                                          
    * precondition: valic Piece object other exists
    * postcondition: this object is created as a copy of other
    */
    Piece(const Piece &other);

    /*
    * description: get number of connected pieces to this
    * return: int number of pieces a this is connected to                                           
    * precondition: valid Piece object exists                           
    * postcondition: int number of pieces a piece is connected to is returned
    */
    int getConnected();

    /*
    * description: connect 2 pieces together
    * return: void, pieces are now connected                                           
    * precondition: orientation reflects the orientation of the piece, for
    *               use in assigning the neighbor piece as connected
    * postcondition: piece and its neighbor are connected
    */
    void connect(Orientation orient);

    /*
    * description: set if a piece has been moved
    * return: void, piece's moved attribute is updated                                       
    * precondition: A valid piece exists
    * postcondition: piece's moved status is updated
    */
    void setMoved(bool moved);

    /*
    * description: check if a piece can be snapped with its neighbor
    * return: boolean true if a piece can be snapped with it's neighbor, false
    *         if not                                         
    * precondition: orientation reflects the orientation of the piece, for
    *               use in determining if the neighbor can be connected
    * postcondition: a boolean is returned, true if a piece can be snapped with
    *               its neighbor, false if not
    */
    bool isSnappable(Orientation orient);

    /*
    * description: update connected neighbor
    * return: void, respective neighbor is updated to be connected                                         
    * precondition: a piece is snapped with one of its neighbors
    * postcondition: the connected array is updated to reflect the piece is 
    *                connected with its neighbor, indicated by orientation
    */
    void setConnected(Orientation orient, bool connected);

    /*
    * description: snap
    * return: Vec2 object representing new position piece should move to snap                                        
    * precondition: a piece is snapped with one of its neighbors
    * postcondition: Vec2 object representing new position to move to
    */
    Vec2 snap(Orientation orient);

    /*
    * description: move
    * return: void, piece is moved to new location and redrawn
    * precondition: a piece is moved
    * postcondition: the piece is moved to its new location and redrawn
    */
    void move(Vec2 newPos, Drawer& drawer, Picture& bg);
    
    /*
    * description: set position
    * return: void, pos attribute is updated to newPos
    * precondition: a valid Piece exists
    * postcondition: pos attribute is set to newPos
    */
    void setPos(const Vec2 &newPos);

    /*
    * description: get position
    * return: Vec2 representing piece position
    * precondition: a valid Piece exists
    * postcondition: pos attribute is returned
    */
    Vec2 getPos() const;

    /*
    * description: isClicked
    * return: boolean, true if piece was clicked on, false if not
    * precondition: a valid Piece exists, point p represents position of mouse
    *               click
    * postcondition: boolean is returned, true if piece was clicked on, false 
    *                if not
    */
    bool isClicked(point p);

    /*
    * description: draw
    * return: void
    * precondition: a valid Piece exists
    * postcondition: Piece is drawn to the screen
    */
    void draw(Drawer& drawer);

    /*
    * description: draw
    * return: void
    * precondition: a valid Piece exists
    * postcondition: Piece is drawn to the screen
    */
    void draw(Drawer& drawer, Picture& pic);
    
    /*
    * description: set Edge
    * return: void
    * precondition: a valid Piece exists
    * postcondition: Piece's edge is updated according to the orientation given
    */
    void setEdge(Orientation orient, Edge edge) {
        switch(orient) {
            case NORMAL:
                topEdge = edge;
                break;
            case RIGHT:
                rEdge = edge;
                break;
            case FLIPPED:
                bottomEdge = edge;
                break;
            case LEFT:
                lEdge = edge;
                break;
        }
    }

    /*
    * description: set Neighbor piece
    * return: void
    * precondition: a valid Piece exists, and a valid Piece neighbor is given
    * postcondition: Piece's neighbor array is updated to include the parameter
    *                neighbor
    */
    void setNeighbor(int index, Piece* neighbor);
};

#endif // PIECE_H_INCLUDED
