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
#ifndef PICTURE_H_INCLUDED
#define PICTURE_H_INCLUDED

#include "SDL_Plotter.h"
#include "vec2.h"
#include <assert.h>
#include <fstream>

class Picture {
    protected:
        bool owner;

    public:
        int width, height;
        // 2d array that contains color of each pixel in picture
        color **picData = nullptr; 
        /*
         * description: move assignment operator
         * return: Picture
         * precondition: The user wants to move a picture
         * postcondition: The picture is moved
        */
        Picture &operator=(Picture &&other); 
        /*
         * description: constructor
         * return: none
         * precondition: The user wants to create a picture with a file
         * postcondition: A picture is created with data from a file
        */
        Picture(string filename);
        /*
         * description: default constructor
         * return: none
         * precondition: The user wants to create a picture
         * postcondition: A picture is created with no data
        */
        Picture() {
            width = 0;
            height = 0;
            picData = nullptr;
        };
        /*
         * description: copy constructor
         * return: none
         * precondition: The user wants to create a picture from another picture
         * postcondition: A picture is created with data from another picture
        */
        Picture(const Picture &other);
        /*
         * description: copy assignment operator
         * return: Picture
         * precondition: The user wants to copy a picture
         * postcondition: A picture is copied
        */
        Picture &operator=(const Picture &other);
        /*
         * description: destructor
         * return: none
         * precondition: The user wants to delete a picture
         * postcondition: A picture is deleted
        */
        virtual ~Picture();
        /*
         * description: returns the dimensions of the picture
         * return: Vec2
         * precondition: The user wants to know the dimensions of the picture
         * postcondition: The dimensions of the picture are returned
        */
        Vec2 dim();
        /*
         * description: returns the color of a pixel
         * return: color
         * precondition: The user wants to know the color of a pixel
         * postcondition: The color of the pixel is returned
        */
        virtual color getPixel(int x, int y);
        /*
         * description: gets the width of the picture
         * return: int
         * precondition: The user wants to know the width of the picture
         * postcondition: The width of the picture is returned
        */
        int getWidth();
        /*
         * description: gets the height of the picture
         * return: int
         * precondition: The user wants to know the height of the picture
         * postcondition: The height of the picture is returned
        */
        int getHeight();
};

enum Orientation { NORMAL, RIGHT, FLIPPED, LEFT };
static Vec2 orientations[4] = {Vec2(0, -1), Vec2(1, 0), Vec2(0, 1),
                               Vec2(-1, 0)};
class Drawer {
    public:
        /*
         * description: constructor
         * return: none
         * precondition: The user wants to create a drawer
         * postcondition: A drawer is created with a plotter
        */
        Drawer(SDL_Plotter &g) : g(g){};
        /*
         * description: draws a picture
         * return: none
         * precondition: The user wants to draw a picture
         * postcondition: A picture is drawn
        */
        void drawPicture(Picture &pic, Vec2 pos, Orientation orient = NORMAL);
        /*
         * description: draws a picture with a mask
         * return: none
         * precondition: The user wants to draw a picture with a mask
         * postcondition: A picture is drawn with a mask
        */
        void drawMask(Picture &pic, Picture &mask, Vec2 maskStart, Vec2 pos,
                      Orientation orient = NORMAL);
        /*
         * description: draws a part of a picture
         * return: none
         * precondition: The user wants to draw a part of a picture
         * postcondition: A part of a picture is drawn
        */
        void drawPart(Picture &pic, Vec2 start, Vec2 dim, Vec2 pos,
                      Orientation orient = NORMAL);

    private:
        SDL_Plotter &g;
        /*
         * description: draws a pixel
         * return: none
         * precondition: The user wants to draw a pixel
         * postcondition: A pixel is drawn
        */
        void drawPixel(int x, int y, color c);
        /*
         * description: draws a picture with its normal orientation
         * return: none
         * precondition: The user wants to draw a picture with its normal
         *              orientation
         * postcondition: A picture is drawn with its normal orientation
        */
        void topOrientationDraw(Picture &pic, Vec2 start, Vec2 dim, Vec2 pos,
                                Orientation orient = NORMAL);
        /*
         * description: draws a picture with its right orientation
         * return: none
         * precondition: The user wants to draw a picture with its right
         * postcondition: A picture is drawn with its right orientation
        */
        void rightOrientationDraw(Picture &pic, Vec2 start, Vec2 dim, Vec2 pos,
                                  Orientation orient = NORMAL);
        /*
         * description: draws a picture with its flipped orientation
         * return: none
         * precondition: The user wants to draw a picture with its flipped
         * postcondition: A picture is drawn with its flipped orientation
        */
        void flippedOrientationDraw(Picture &pic, Vec2 start, Vec2 dim,
                                    Vec2 pos, Orientation orient = NORMAL);
        /*
         * description: draws a picture with its left orientation
         * return: none
         * precondition: The user wants to draw a picture with its left
         * postcondition: A picture is drawn with its left orientation
        */
        void leftOrientationDraw(Picture &pic, Vec2 start, Vec2 dim, Vec2 pos,
                                 Orientation orient = NORMAL);
        /*
         * description: draws a picture with a mask and its normal orientation
         * return: none
         * precondition: The user wants to draw a picture with a mask and its
         *             normal orientation
         * postcondition: A picture is drawn with a mask and its normal
        */
        void topOrientationMask(Picture &pic, Picture &mask, Vec2 maskStart,
                                Vec2 pos, Orientation orient = NORMAL);
        /*
         * description: draws a picture with a mask and its right orientation
         * return: none
         * precondition: The user wants to draw a picture with a mask and its
         *            right orientation
         * postcondition: A picture is drawn with a mask and its right
         *               orientation
        */
        void rightOrientationMask(Picture &pic, Picture &mask, Vec2 maskStart,
                                  Vec2 pos, Orientation orient = NORMAL);
        /*
         * description: draws a picture with a mask and its flipped orientation
         * return: none
         * precondition: The user wants to draw a picture with a mask and its
         *           flipped orientation
         * postcondition: A picture is drawn with a mask and its flipped
         *              orientation
        */
        void flippedOrientationMask(Picture &pic, Picture &mask, Vec2 maskStart,
                                    Vec2 pos, Orientation orient = NORMAL);
        /*
         * description: draws a picture with a mask and its left orientation
         * return: none
         * precondition: The user wants to draw a picture with a mask and its
         *          left orientation
         * postcondition: A picture is drawn with a mask and its left
         *              orientation
        */
        void leftOrientationMask(Picture &pic, Picture &mask, Vec2 maskStart,
                                 Vec2 pos, Orientation orient = NORMAL);
};

class Background : public Picture {
    public:
        /*
         * description: constructor
         * return: none
         * precondition: The user wants to create a background
         * postcondition: A background is created
        */
        Background() {
            width = 0;
            height = 0;
            picData = nullptr;
            owner = false;
        }
        /*
         * description: destructor
         * return: none
         * precondition: The user wants to delete a background
         * postcondition: A background is deleted
        */
        ~Background() { owner = false; }
        /*
         * description: gets the color of a pixel
         * return: color
         * precondition: The user wants to know the color of a pixel
         * postcondition: The color of the pixel is returned (always white)
        */
        color getPixel(int x, int y) override { return color(255, 255, 255); };
};
#endif // PICTURE_H_INCLUDED
