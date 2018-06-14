#include "node.h"
#include <fstream>

void node::insert(void)
{
    is_leaf = false;

    northWest = new node(x-dx/4.0, y+dy/4.0, dx/2.0, dy/2.0, level*10+0, level+1);
    southWest = new node(x-dx/4.0, y-dy/4.0, dx/2.0, dy/2.0, level*10+1, level+1);
    northEast = new node(x+dx/4.0, y+dy/4.0, dx/2.0, dy/2.0, level*10+2, level+1);
    southEast = new node(x+dx/4.0, y-dy/4.0, dx/2.0, dy/2.0, level*10+3, level+1);
}

void node::printNode(void)
{
    std::cout << "NODE LEVEL: " << level << std::endl;
    std::cout << "Node center     ( x,  y): (" << x << ", " << y << ")" << std::endl;
    std::cout << "Node dimensions (dx, dy): (" << dx << ", " << dy << ")" << std::endl;
}

void node::printNode2(void)
{
    // Print cell centers to the terminal for plotting and verification
    std::cout << x << "    " << y << "    " << is_leaf << std::endl;
}

void node::refine(void)
{
    // Prevent excessive refinement (refinement creates 4^(max_level) nodes which can cause segfaults)
    int max_level = 2;

    if (this->level >= max_level)
    {
        //std::cout << "Exceeded " << max_level << " levels of refinement. Exiting...\n";
        return;
    }
    else
    {
        // Node will now have children, so it is no longer a leaf
        is_leaf = false;

        northWest = new node(x-dx/4.0, y+dy/4.0, dx/2.0, dy/2.0, level*10+0, level+1);
        northWest->printNode2();
        northWest->refine();

        southWest = new node(x-dx/4.0, y-dy/4.0, dx/2.0, dy/2.0, level*10+1, level+1);
        southWest->printNode2();
        southWest->refine();

        northEast = new node(x+dx/4.0, y+dy/4.0, dx/2.0, dy/2.0, level*10+2, level+1);
        northEast->printNode2();
        northEast->refine();

        southEast = new node(x+dx/4.0, y-dy/4.0, dx/2.0, dy/2.0, level*10+3, level+1);
        southEast->printNode2();
        southEast->refine();
    }
}

bool node::inBoundary(float p_x, float p_y)
{
    // Calculate bounding box extent 
    float xMin = x - dx/2.0;
    float xMax = x + dx/2.0;
    float yMin = y - dy/2.0;
    float yMax = y + dy/2.0;

    // Boolean result of if the input coordinates are within the node boundary
    return (p_x >= xMin && 
            p_x <= xMax &&
            p_y >= yMin &&
            p_y <= yMax);
}

void node::traverseTree(const std::string &pc_output)
{
    std::ofstream pointfile;
    pointfile.open (pc_output);

    recurseTree(pointfile);

    pointfile.close();
}

void node::recurseTree(std::ostream &pointfile)
{
    pointfile << x << "    " << y << std::endl;

    if (is_leaf == false)
    {
        northWest->recurseTree(pointfile);
        southWest->recurseTree(pointfile);
        northEast->recurseTree(pointfile);
        southEast->recurseTree(pointfile);
    } 
    else
    {
        return;
    }
}
