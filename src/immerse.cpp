
#include <iostream>
#include <vector>

// implement later after the basics are working
/*struct point
{
    // generic point, for reuse
    float x;
    float y;

    // constructor
    point(float _x, float _y) { x = _x; y = _y; }
    // additional default constructor
    point () { x = 0.0; y = 0.0; }
};*/

class nGon {
public:
    // the input polygon to immerse
    int numEdges;
    std::vector<int> edgeList();
    std::vector<float> vertX(), vertY();
    float dx, dy;
    // hide to debug
   // boundBox nGonBbox;

    float findMin(std::vector<float>*);
    float findMax(std::vector<float>*);
    float createBoundary(void);
};

float nGon::findMin(std::vector<float>* inpArray) {

    float min = inpArray[0];

    for (int n = 1; n < numEdges; n++) {
        if (inpArray[n] < min) {
            min = inpArray[n];
        }
    }
    return min;
}

float nGon::findMax (std::vector<float>* inpArray) {

    float max = inpArray[0];

    for (int n = 1; n < numEdges; n++) {
        if (inpArray[n] > max) {
            max = inpArray[n];
        }
    }
    return max;
}

float nGon::createBoundary(void)
{
    // find min and max of x vertices 
    float xMin = findMin(&vertX);
    float xMax = findMax(&vertX);
    // find min and max of y vertices 
    float yMin = findMin(&vertY);
    float yMax = findMax(&vertY);
    // calculate bounding box dimensions 
    // expand by 10% each side 
    dx = xMax - xMin;
    dy = yMax - yMin;

    xMin = xMin - 0.05*dx;
    xMax = xMax + 0.05*dx;
    yMin = yMin - 0.05*dy;
    yMax = yMax + 0.05*dy;

    float bBoxX[] = {xMin, xMin, xMax, xMax};
    float bBoxY[] = {yMin, yMax, yMax, yMin};
}

class node {
   
    float x, y;
    float dx, dy;
    int data;
    int level;
public:
    node *northWest;
    node *northEast;
    node *southWest;
    node *southEast;

 //public:    
    node (float _x, float _y, float _dx, float _dy, int _data, int _level) {
        x     = _x; 
        y     = _y;
        dx    = _dx;
        dy    = _dy;
        data  = _data;
        level = _level;

        northWest = NULL;
        northEast = NULL;
        southWest = NULL;
        southEast = NULL;
    }
    node () {
        northWest = NULL;
        northEast = NULL;
        southWest = NULL;
        southEast = NULL;
    }
    void insert(void);
    void printNode(void);
};

void node::insert(void) {

    northWest = new node(x-dx/4.0, y+dy/4.0, dx/2.0, dy/2.0, level*10+0, level+1);
    southWest = new node(x-dx/4.0, y-dy/4.0, dx/2.0, dy/2.0, level*10+1, level+1);
    northEast = new node(x+dx/4.0, y+dy/4.0, dx/2.0, dy/2.0, level*10+2, level+1);
    southEast = new node(x+dx/4.0, y-dy/4.0, dx/2.0, dy/2.0, level*10+3, level+1);
}

void node::printNode(void) {
    
    std::cout << "NODE LEVEL: " << level << std::endl;
    std::cout << "Node center     ( x,  y): (" << x << ", " << y << ")" << std::endl;
    std::cout << "Node dimensions (dx, dy): (" << dx << ", " << dy << ")" << std::endl;
}

/*

bool node::inBoundary(point p)
{
    // bounding box extent 
    float xMin = nodeBound.centerX - nodeBound.bBoxDx/2.0;
    float xMax = nodeBound.centerX + nodeBound.bBoxDx/2.0;
    float yMin = nodeBound.centerY - nodeBound.bBoxDy/2.0;
    float yMax = nodeBound.centerY + nodeBound.bBoxDy/2.0;

    return (p.x >= xMin && 
            p.x <= xMax &&
            p.y >= yMin &&
            p.y <= yMax);

}*/

int main () {

    // trivial two-dimensional n-gon

    nGon polygon0; 
    /*
//    int nGon = 4;
    float vertX[] = {2.0, 1.0, 4.0, 5.0};
    float vertY[] = {1.0, 3.0, 4.0, 2.0};
    float bBoxDx, bBoxDy;
    int edgeList[] = {0, 1, 1, 2, 2, 3, 3, 0};
    */

    // working quadtree 
    node *root0;
    root0 = new node(4.0, 3.0, 2.0, 2.0, 1, 0);
    
    node *tempPtr = new node(*root0);
    for (int i = 0; i < 10; i++) {

        (*tempPtr).insert();
        (*tempPtr).printNode();

        tempPtr = (*tempPtr).northWest;
    }

    return 0;
}
