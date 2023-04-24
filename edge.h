#ifndef edge_h
#define edge_h

#include "picture.h"

class Edge {
    public:
        Edge(Picture *pic): pic(pic), inverted(false) {}
        Edge(Picture *pic, bool inverted): pic(pic), inverted(inverted) {}
    private:
        Picture *pic;
        bool inverted;
}

#endif // edge.h
