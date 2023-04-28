#ifndef edgeloader_h
#define edgeloader_h

#include "picture.h"

class EdgeLoader {
    private:
        Picture **edges;
        int numEdges;
    public:
        EdgeLoader();
        ~EdgeLoader();
        Picture *getRandomEdge(bool &isFlipped);
};

#endif // edgeloader.h
