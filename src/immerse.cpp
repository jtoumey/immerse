
#include <iostream>
#include <vector>
#include <fstream>

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
    std::vector<float> vertX;
    std::vector<float> vertY;
    float dx, dy;
    float xMin, xMax, yMin, yMax;
    float c_x, c_y; // center

    void createBoundary(void);
    float findMin(std::vector<float>);
    float findMax(std::vector<float>);
};

void nGon::createBoundary(void)
{


    // find min and max of x vertices 
    xMin = findMin(vertX);
    xMax = findMax(vertX);
    yMin = findMin(vertY);
    yMax = findMax(vertY);


    // calculate bounding box dimensions 
    // expand by 10% each side 
    dx = xMax - xMin;
    dy = yMax - yMin;

    c_x = xMin + dx/2.0;
    c_y = yMin + dy/2.0;

    xMin = xMin - 0.05*dx;
    xMax = xMax + 0.05*dx;
    yMin = yMin - 0.05*dy;
    yMax = yMax + 0.05*dy;

}
float nGon::findMin(std::vector<float> vert) {
    float min;
    min = vert[0];
    for (int n = 1; n < numEdges; n++) {
        if (vert[n] < min) {
            min = vert[n];
        }
    }
    return min;
}
float nGon::findMax(std::vector<float> vert) {
    float max;
    max = vert[0];
    for (int n = 1; n < numEdges; n++) {
        if (vert[n] > max) {
            max = vert[n];
        }
    }
    return max;
}
class node {
public:   
    float x, y;
    float dx, dy;
    int data;
    int level;
//public:
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
    void printNode2(void);
    void refine(void);
    void writeFile(void);
    bool inBoundary(float, float);
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

void node::printNode2(void) {
    std::cout << x << "    " << y << std::endl;
}

void node::refine(void) {
    int max_level = 3;
    if (this->level >= max_level) {
        //std::cout << "Exceeded " << max_level << " levels of refinement. Exiting...\n";
        return;
    }
    else {
        northWest = new node(x-dx/4.0, y+dy/4.0, dx/2.0, dy/2.0, level*10+0, level+1);
        //this->printNode();
        northWest->printNode2();
        northWest->refine();

        southWest = new node(x-dx/4.0, y-dy/4.0, dx/2.0, dy/2.0, level*10+1, level+1);
        southWest->printNode2();
        southWest->refine();

        northEast = new node(x+dx/4.0, y+dy/4.0, dx/2.0, dy/2.0, level*10+2, level+1);
        northEast->refine();
        northEast->printNode2();

        southEast = new node(x+dx/4.0, y-dy/4.0, dx/2.0, dy/2.0, level*10+3, level+1);
        southEast->refine();
        southEast->printNode2();
    }
}

bool node::inBoundary(float p_x, float p_y)
{
    // bounding box extent 
    float xMin = x - dx/2.0;
    float xMax = x + dx/2.0;
    float yMin = y - dy/2.0;
    float yMax = y + dy/2.0;

    return (p_x >= xMin && 
            p_x <= xMax &&
            p_y >= yMin &&
            p_y <= yMax);

}

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

    //void foo (std::ofstream& dumFile) {}

    //ofstream pc_output;
    //pc_output.open("pc_output.dat");

    node *root1;
    //root1 = new node(polygon0.c_x, polygon0.c_y, polygon0.dx, polygon0.dy, 1, 0);
    root1 = new node(2.0, 2.0, 4.0, 4.0, 1, 0);

    node *temp2 = new node(*root1);

    node *parentKey;
    parentKey = temp2;

    (*parentKey).printNode2();

    (*parentKey).refine();

    //pc_output.close();


    return 0;
}
