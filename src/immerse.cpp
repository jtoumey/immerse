#include "nGon.h"
#include "node.h"

int main () {

    // trivial two-dimensional n-gon
    nGon polygon0; 
    // x vertices: {2.0, 1.0, 4.0, 5.0};
    // y vertices: {1.0, 3.0, 4.0, 2.0};
    //int edgeList[] = {0, 1, 1, 2, 2, 3, 3, 0};

    polygon0.numEdges = 4;

    // sloppy way just to test the polygon creation
    polygon0.vertX.push_back(2.0);
    polygon0.vertX.push_back(1.0);
    polygon0.vertX.push_back(4.0);
    polygon0.vertX.push_back(5.0);

    polygon0.vertY.push_back(1.0);
    polygon0.vertY.push_back(3.0);
    polygon0.vertY.push_back(4.0);
    polygon0.vertY.push_back(2.0);

    polygon0.createBoundary();

    // working quadtree 
    node *root0;
    root0 = new node(4.0, 3.0, 2.0, 2.0, 1, 0);
    
    node *tempPtr = new node(*root0);
    for (int i = 0; i < 10; i++) {

        (*tempPtr).insert();
        (*tempPtr).printNode();

        tempPtr = (*tempPtr).northWest;
    }

    node *root1;
    //root1 = new node(polygon0.c_x, polygon0.c_y, polygon0.dx, polygon0.dy, 1, 0);
    root1 = new node(2.0, 2.0, 4.0, 4.0, 1, 0);

    node *temp2 = new node(*root1);

    node *parentKey;
    parentKey = temp2;

    (*parentKey).printNode2();

    (*parentKey).refine();

    return 0;
}
