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
    numEdges = 10;
    edges = new Picture *[numEdges];
    edges[0] = new Picture("./pictureTXTs/edges/sidebump.png.txt");
    edges[1] = new Picture("./pictureTXTs/edges/Bumpy.png.txt");
    edges[2] = new Picture("./pictureTXTs/edges/biggump.png.txt");
    edges[3] = new Picture("./pictureTXTs/edges/cauldron.png.txt");
    edges[4] = new Picture("./pictureTXTs/edges/dog.png.txt");
    edges[5] = new Picture("./pictureTXTs/edges/hook.png.txt");
    edges[6] = new Picture("./pictureTXTs/edges/mushrooms.png.txt");
    edges[7] = new Picture("./pictureTXTs/edges/teeth.png.txt");
    edges[8] = new Picture("./pictureTXTs/edges/horns.png.txt");
    edges[9] = new Picture("./pictureTXTs/edges/Claudia.png.txt");
}

EdgeLoader::~EdgeLoader() {
    cout << "load delete" << endl;
    for (int i = 0; i < numEdges; i++) {
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
