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
#ifndef vec2_h
#define vec2_h

#include "SDL_Plotter.h"
#include <iostream>

struct iVec2 {
    public:
        int x, y;
        /*
         * description: operator<<
         * return: ostream (for chaining)
         * precondition: The user wants to print the vector
         * postcondition: The vector is printed to the ostream
         */
        friend std::ostream &operator<<(std::ostream &os, iVec2 v);
};

struct Vec2 {
    public:
        float x, y;
        /*
         * description: Converts a Vec2 to an iVec2
         * return: iVec2
         * precondition: The user wants to convert a Vec2 to an iVec2
         * postcondition: The Vec2 is converted to an iVec2
         */
        iVec2 toIVec2();
        /*
         * description: Constructor
         * return: None
         * precondition: The user wants to create a Vec2
         * postcondition: A Vec2 is created
         */
        Vec2(float x, float y);
        /*
         * description: operator+
         * return: Vec2
         * precondition: The user wants to add two vectors
         * postcondition: The vectors are added
         */
        Vec2 operator+(Vec2 other);
        /*
         * description: operator-
         * return: Vec2
         * precondition: The user wants to subtract two vectors
         * postcondition: The vectors are subtracted
         */
        Vec2 operator-(Vec2 other);
        /*
         * description: operator*
         * return: Vec2
         * precondition: The user wants to multiply a vector by a scalar
         * postcondition: The vector is multiplied by the scalar
         */
        Vec2 operator*(float scalar);
        /*
         * description: operator/
         * return: Vec2
         * precondition: The user wants to divide a vector by a scalar
         * postcondition: The vector is divided by the scalar
         */
        Vec2 operator/(float scalar);
        /*
         * description: operator+=
         * return: Vec2
         * precondition: The user wants to add two vectors
         * postcondition: The vectors are added
         */
        Vec2 operator+=(Vec2 other);
        /*
         * description: operator-=
         * return: Vec2
         * precondition: The user wants to subtract two vectors
         * postcondition: The vectors are subtracted
         */
        Vec2 operator-=(Vec2 other);
        /*
         * description: operator*=
         * return: Vec2
         * precondition: The user wants to multiply a vector by a scalar
         * postcondition: The vector is multiplied by the scalar
         */
        Vec2 operator*=(float scalar);
        /*
         * description: operator/=
         * return: Vec2
         * precondition: The user wants to divide a vector by a scalar
         * postcondition: The vector is divided by the scalar
         */
        Vec2 operator/=(float scalar);
        /*
         * description: flip
         * return: Vec2
         * precondition: The user wants to flip a vector
         * postcondition: The vector's x and y components are swapped
         */
        Vec2 flip();
        /*
         * description: ycomp
         * return: Vec2
         * precondition: The user wants to get the y component of a vector
         * postcondition: The y component of the vector is returned (x = 0)
         */
        Vec2 ycomp();
        /*
         * description: xcomp
         * return: Vec2
         * precondition: The user wants to get the x component of a vector
         * postcondition: The x component of the vector is returned (y = 0)
         */
        Vec2 xcomp();
        /*
         * description: splatx
         * return: Vec2
         * precondition: The user wants to get the x component of a vector
         * postcondition: The x component of the vector is returned (y = x)
         */
        Vec2 splatx();
        /*
         * description: splaty
         * return: Vec2
         * precondition: The user wants to get the y component of a vector
         * postcondition: The y component of the vector is returned (x = y)
         */
        Vec2 splaty();
        /*
         * description: operator<<
         * return: ostream (for chaining)
         * precondition: The user wants to print the vector
         * postcondition: The vector is printed to the ostream
         */
        friend std::ostream &operator<<(std::ostream &os, Vec2 v);
        /*
         * description: fromPoint
         * return: Vec2
         * precondition: The user wants to convert a point to a vector
         * postcondition: The point is converted to a vector
         */
        static Vec2 fromPoint(point p);
        /*
         * description: toPoint
         * return: point
         * precondition: The user wants to convert a vector to a point
         * postcondition: The vector is converted to a point
         */
        point toPoint();
        /*
         * description: sqMagnitude
         * return: float
         * precondition: The user wants the squared magnitude of a vector
         * postcondition: The squared magnitude of the vector is returned
         */
        float sqMagnitude();
        /*
         * description: dot
         * return: float
         * precondition: The user wants the dot product of two vectors
         * postcondition: The dot product of the vectors is returned
         */
        float dot(Vec2 other);
        /*
         * description: magnitude
         * return: float
         * precondition: The user wants the magnitude of a vector
         * postcondition: The magnitude of the vector is returned
         */
        float magnitude();
        /*
         * description: normalized
         * return: Vec2
         * precondition: The user wants the normalized vector
         * postcondition: The normalized vector is returned
         */
        Vec2 normalized();
};

const Vec2 L = Vec2(-1, 0);
const Vec2 R = Vec2(1, 0);
const Vec2 UP = Vec2(0, 1);
const Vec2 DOWN = Vec2(0, -1);
const Vec2 UNIT = Vec2(1, 1);

#endif // vec2.h
