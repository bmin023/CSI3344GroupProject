#ifndef vec2_h
#define vec2_h

#include <iostream>

struct iVec2 {
  int x, y;
  friend std::ostream &operator<<(std::ostream &os, iVec2 v) {
    os << "(" << v.x << ", " << v.y << ")";
    return os;
  }
};

struct Vec2 {
  float x, y;
  iVec2 toIVec2() {
    return {static_cast<int>(x), static_cast<int>(y)};
  }
  Vec2(float x, float y) : x(x), y(y) {}
  Vec2 operator+(Vec2 other) { return Vec2(x + other.x, y + other.y); }
  Vec2 operator-(Vec2 other) { return Vec2(x - other.x, y - other.y); }
  Vec2 operator*(float scalar) { return Vec2(x * scalar, y * scalar); }
  Vec2 operator/(float scalar) { return Vec2(x / scalar, y / scalar); }
  Vec2 operator+=(Vec2 other) {
    x += other.x;
    y += other.y;
    return *this;
  }
  Vec2 operator-=(Vec2 other) {
    x -= other.x;
    y -= other.y;
    return *this;
  }
  Vec2 operator*=(float scalar) {
    x *= scalar;
    y *= scalar;
    return *this;
  }
  Vec2 operator/=(float scalar) {
    x /= scalar;
    y /= scalar;
    return *this;
  }
  Vec2 flip() { return Vec2(y, x); }
  Vec2 ycomp() { return Vec2(0, y); }
  Vec2 xcomp() { return Vec2(x, 0); }
  Vec2 splatx() { return Vec2(x, x); }
  Vec2 splaty() { return Vec2(y, y); }
  friend std::ostream &operator<<(std::ostream &os, Vec2 v) {
    os << "(" << v.x << ", " << v.y << ")";
    return os;
  }
  static Vec2 fromPoint(point p) { return Vec2(p.x, p.y); }
  point toPoint() { return {static_cast<int>(x), static_cast<int>(y)}; }
  float sqMagnitude() { return x * x + y * y; }
  float dot(Vec2 other) { return x * other.x + y * other.y; }
};

const Vec2 L = Vec2(-1,0);
const Vec2 R = Vec2(1, 0);
const Vec2 UP = Vec2(0, 1);
const Vec2 DOWN = Vec2(0,-1);
const Vec2 UNIT = Vec2(1,1);

#endif // vec2.h
