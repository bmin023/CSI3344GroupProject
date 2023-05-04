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
#include "edgeloader.h"
#include <dirent.h>

EdgeLoader::EdgeLoader() {
    // set random seed
    srand(time(NULL));
    // // traverse through the directory and load all the edges
    // // picturTXTs/egdes is the directory
    // DIR *dir;
    // dir = opendir("./pictureTXTs/edges");
    //
    // edges = new Picture *[numEdges];
    //
    // dirent *d;
    // this->numEdges = 0;
    // while ((d = readdir(dir)) != NULL) {
    //     if (d->d_name[0] != '.') {
    //         numEdges++;
    //         cout << "Loading edge " << numEdges << ": " << d->d_name << endl;
    //         edges[numEdges - 1] =
    //             new Picture("./pictureTXTs/edges/" + string(d->d_name));
    //     }
    // }
    // closedir(dir);
    // cout << "Loaded " << numEdges << " edges." << endl;
    numEdges = 9;
    edges = new Picture*[numEdges];
    edges[0] = new Picture("./pictureTXTs/edges/sidebump.png.txt");
    edges[1] = new Picture("./pictureTXTs/edges/Bumpy.png.txt");
    edges[2] = new Picture("./pictureTXTs/edges/biggump.png.txt");
    edges[3] = new Picture("./pictureTXTs/edges/cauldron.png.txt");
    edges[4] = new Picture("./pictureTXTs/edges/dog.png.txt");
    edges[5] = new Picture("./pictureTXTs/edges/hook.png.txt");
    edges[6] = new Picture("./pictureTXTs/edges/mushrooms.png.txt");
    edges[7] = new Picture("./pictureTXTs/edges/teeth.png.txt");
    edges[8] = new Picture("./pictureTXTs/edges/horns.png.txt");
    // edges[9] = new Picture("./pictureTXTs/edges/Claudia.png.txt");
}

EdgeLoader::EdgeLoader(const EdgeLoader& other) {
    numEdges = other.numEdges;
    edges = new Picture*[numEdges];
    for(int i = 0; i < numEdges; i++) {
        edges[i] = new Picture(*other.edges[i]);
    }
}

EdgeLoader& EdgeLoader::operator=(const EdgeLoader& other) {
    if(this != &other) {
        if(edges != nullptr) {
            for(int i = 0; i < numEdges; i++) {
                delete edges[i];
            }
            delete [] edges;
        }
        numEdges = other.numEdges;
        edges = new Picture*[numEdges];
        for(int i = 0; i < numEdges; i++) {
            edges[i] = new Picture(*other.edges[i]);
        }
    }
    return *this;
}

EdgeLoader::~EdgeLoader() {
    for(int i = 0; i < numEdges; i++) {
        delete edges[i];
    }
    delete[] edges;
}

Picture *EdgeLoader::getRandomEdge(bool &isFlipped) {
    int randEdge = rand() % numEdges;
    Picture *edge = edges[randEdge];
    isFlipped = rand() % 2;
    return edge;
}
