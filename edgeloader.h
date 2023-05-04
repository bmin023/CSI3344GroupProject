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
