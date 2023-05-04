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
#include "vec2.h"
std::ostream &operator<<(std::ostream &os, iVec2 v);

iVec2 Vec2::toIVec2() { return {static_cast<int>(x), static_cast<int>(y)}; }
Vec2::Vec2(float x, float y) : x(x), y(y) {}
Vec2 Vec2::operator+(Vec2 other) { return Vec2(x + other.x, y + other.y); }
Vec2 Vec2::operator-(Vec2 other) { return Vec2(x - other.x, y - other.y); }
Vec2 Vec2::operator*(float scalar) { return Vec2(x * scalar, y * scalar); }
Vec2 Vec2::operator/(float scalar) { return Vec2(x / scalar, y / scalar); }
Vec2 Vec2::operator+=(Vec2 other) {
    x += other.x;
    y += other.y;
    return *this;
}
Vec2 Vec2::operator-=(Vec2 other) {
    x -= other.x;
    y -= other.y;
    return *this;
}
Vec2 Vec2::operator*=(float scalar) {
    x *= scalar;
    y *= scalar;
    return *this;
}
Vec2 Vec2::operator/=(float scalar) {
    x /= scalar;
    y /= scalar;
    return *this;
}
Vec2 Vec2::flip() { return Vec2(y, x); }
Vec2 Vec2::ycomp() { return Vec2(0, y); }
Vec2 Vec2::xcomp() { return Vec2(x, 0); }
Vec2 Vec2::splatx() { return Vec2(x, x); }
Vec2 Vec2::splaty() { return Vec2(y, y); }
std::ostream &operator<<(std::ostream &os, Vec2 v) {
    os << "(" << v.x << ", " << v.y << ")";
    return os;
}
Vec2 Vec2::fromPoint(point p) { return Vec2(p.x, p.y); }
point Vec2::toPoint() { return {static_cast<int>(x), static_cast<int>(y)}; }
float Vec2::sqMagnitude() { return x * x + y * y; }
float Vec2::dot(Vec2 other) { return x * other.x + y * other.y; }
float Vec2::magnitude() { return sqrt(sqMagnitude()); }
Vec2 Vec2::normalized() { return *this / magnitude(); }
