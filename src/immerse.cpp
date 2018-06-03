
#include <iostream>

struct point
{
    // generic point, for reuse
    float x;
    float y;

    // constructor
    point(float _x, float _y) { x = _x; y = _y; }
    // additional default constructor
    point () { x = 0.0; y = 0.0; }
};

struct treeNode
{
    // a subdivision of the quadtree

    // node location
    point loc;

    // information regarding intersection at node
    int nodeData;
    // constructors
    treeNode ( point _loc, int _nodeData ) { loc = _loc; nodeData = _nodeData; }
    // default, no position 
    treeNode () { nodeData = 0; }
};

struct boundBox
{
    // general bound box for polygon
    // future implementation
    //std::vector<float> center;
    // or just make this a struct point
    float centerX;
    float centerY;

    float bBoxDx;
    float bBoxDy;
    boundBox ( float _centerX, float _centerY, float _bBoxDx, float _bBoxDy ) 
    {
        centerX = _centerX;
        centerY = _centerY;
        bBoxDx = _bBoxDx;
        bBoxDy = _bBoxDy;
    }
    boundBox () { centerX = 0.0; centerY = 0.0; bBoxDx = 0.0; bBoxDy = 0.0; } 
};

struct nGon
{
    // the input polygon to immerse
    int numEdges;
    std::vector<int> edgeList();
    std::vector<float> vertX(), vertY();
    // hide to debug
   // boundBox nGonBbox;
};

class quadTree {

    // for the current node in the tree, reuse the boundBox to store node geometry
    boundBox nodeBound;

    // for the current node, store location and intersection data
    treeNode *n;

    // child nodes
    quadTree *nw;
    quadTree *ne;
    quadTree *se;
    quadTree *sw;

    public:
        // default constructor
        quadTree ()
        {
            nodeBound = boundBox(0, 0, 0, 0);
            n = NULL;
            nw = NULL;
            ne = NULL;
            se = NULL;
            sw = NULL;
        }
        // constructor
        quadTree (boundBox _bound)
        {
            nodeBound = boundBox(_bound);
            n = NULL;
            nw = NULL;
            ne = NULL;
            se = NULL;
            sw = NULL;
        }
    void insert(treeNode*);
    treeNode* search(point);
    bool inBoundary(point);
};

// member fcns
void quadTree::insert(treeNode *node) { 

    if ( node == NULL)
        return;

    if (!inBoundary(node->loc))
        return;

    if ( nodeBound.bBoxDx <= 1.0 && 
         nodeBound.bBoxDy <= 1.0 )
    {
        if ( n == NULL)
            n = node;
        return;
    }

    // compare the center of current node to center of passed in node
    // if the x coordinate of current node center exceeds that of passed in, it's left hand side
    if ( nodeBound.centerX >= node->loc.x )
    {
        // now test the y coordinate
        if (  nodeBound.centerY >= node->loc.y )
        {
            if ( nw == NULL )
                nw = new quadTree( boundBox( nodeBound.centerX - nodeBound.bBoxDx/4.0, nodeBound.centerY + nodeBound.bBoxDy/4.0, nodeBound.bBoxDx/2.0, nodeBound.bBoxDy/2.0));
            nw->insert(node);
        }
        else
        {
            if ( sw == NULL )
                sw = new quadTree( boundBox( nodeBound.centerX - nodeBound.bBoxDx/4.0, nodeBound.centerY - nodeBound.bBoxDy/4.0, nodeBound.bBoxDx/2.0, nodeBound.bBoxDy/2.0));
            sw->insert(node);
        }
    }
    else
    {
        // now test the y coordinate
        if ( nodeBound.centerY >= node->loc.y )
        {
            if ( ne == NULL )
                ne = new quadTree( boundBox( nodeBound.centerX + nodeBound.bBoxDx/4.0, nodeBound.centerY + nodeBound.bBoxDy/4.0, nodeBound.bBoxDx/2.0, nodeBound.bBoxDy/2.0));
            ne->insert(node);
        }
        else
        {
            if ( se == NULL )
                se = new quadTree( boundBox(nodeBound.centerX + nodeBound.bBoxDx/4.0, nodeBound.centerY - nodeBound.bBoxDy/4.0, nodeBound.bBoxDx/2.0, nodeBound.bBoxDy/2.0));
            se->insert(node);
        }
    }
}

bool quadTree::inBoundary(point p)
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

}

float findMin (int dim, float inpArray[]) {
    float min = inpArray[0];
    for( int n = 1; n < dim; n++) {
        if ( inpArray[n] < min ) {
            min = inpArray[n];
        }
    }
    return min;
}

float findMax (int dim, float inpArray[]) {
    float max = inpArray[0];
    for( int n = 1; n < dim; n++) {
        if ( inpArray[n] > max ) {
            max = inpArray[n];
        }
    }
    return max;
}

int main () {

    // trivial two-dimensional n-gon

    nGon polygon0; 
    /*
//    int nGon = 4;
    float vertX[] = {2.0, 1.0, 4.0, 5.0};
    float vertY[] = {1.0, 3.0, 4.0, 2.0};
    float bBoxDx, bBoxDy;
    int edgeList[] = {0, 1, 1, 2, 2, 3, 3, 0};
    float xMin, xMax, yMin, yMax;

    // find dimensions for bounding box with O(n) search
    xMin = findMin(nGon, vertX);
    xMax = findMax(nGon, vertX);
    yMin = findMin(nGon, vertY);
    yMax = findMax(nGon, vertY);

    // define bounding box and grow x and y by 10%
    bBoxDx = xMax - xMin;
    bBoxDy = yMax - yMin;

    xMin = xMin - 0.05*bBoxDx;
    xMax = xMax + 0.05*bBoxDx;
    yMin = yMin - 0.05*bBoxDy;
    yMax = yMax + 0.05*bBoxDy;

    float bBoxX[] = {xMin, xMin, xMax, xMax};
    float bBoxY[] = {yMin, yMax, yMax, yMin};

    // test print
    std::cout << "B box coordinates:\n";
    for ( int n = 0; n < nGon; n++ ) {
        std::cout << "(x, y) = (" << bBoxX[n] << ", " << bBoxY[n] << ")\n";
    }
    */
}
