#ifndef edgeloader_h
#define edgeloader_h

#include "picture.h"

class EdgeLoader {
    private:
        Picture **edges = nullptr;
    
    public:
        int numEdges;
        EdgeLoader();
        EdgeLoader(const EdgeLoader &other);
        EdgeLoader &operator=(const EdgeLoader &other);
        EdgeLoader &operator=(EdgeLoader &&other) {
            if (this != &other) {
                if (this->edges != nullptr) {
                    for (int i = 0; i < numEdges; i++) {
                        delete edges[i];
                    }
                    delete[] edges;
                }
                edges = other.edges;
                other.edges = nullptr;
                numEdges = other.numEdges;
                other.numEdges = 0;
            }
            return *this;
        }
        ~EdgeLoader();
        void report() {
            for(int i = 0; i < numEdges; i++) {
                cout << "Edge " << i << ": ";
                edges[i]->report();
            }
        }
        Picture *getRandomEdge(bool &isFlipped);
};

#endif // edgeloader.h
