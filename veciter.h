#ifndef veciter_h
#define veciter_h

#include "picture.h"
#include "vec2.h"

//starts at the top right and goes down
class veciter {
    private:
        int x,y;
        Orientation orient;
    public:
        veciter(Vec2 start, Vec2 dim, Orientation orient) {
            this->orient = orient;
            switch (orient) {
                case NORMAL:
                    x = start.x;
                    y = start.y;
                    break;
                case RIGHT:
                    x = start.x + dim.y;
                    y = start.y;
                    break;
                case LEFT:
                    x = start.x;
                    y = start.y + dim.x;
                    break;
            }
        }
        Vec2 next() {
            return Vec2(i,j);
        }
};
#endif // veciter_h
