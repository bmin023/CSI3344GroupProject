#ifndef vec2_h
#define vec2_h

struct iVec2 {
  int x, y;
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
};

#endif // vec2.h
