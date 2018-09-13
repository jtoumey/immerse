#include "node.h"
#include <fstream>

int node::max_level = 2;
bool node::print_flag = true;

node::node () 
{
    is_leaf = true;
    northWest = NULL;
    northEast = NULL;
    southWest = NULL;
    southEast = NULL;
}

node::node (float _x, float _y, float _dx, float _dy, int _data, int _level) 
{
    x     = _x; 
    y     = _y;
    dx    = _dx;
    dy    = _dy;
    data  = _data;
    level = _level;

    is_leaf = true;
    northWest = NULL;
    northEast = NULL;
    southWest = NULL;
    southEast = NULL;
}

void node::printNode(void)
{
    std::cout << "*************************"  << std::endl;
    std::cout << "              Node level: " << level << std::endl;
    std::cout << "        Node leaf status: " << is_leaf << std::endl;
    std::cout << "Node center     ( x,  y): (" << x << ", " << y << ")" << std::endl;
    std::cout << "Node dimensions (dx, dy): (" << dx << ", " << dy << ")" << std::endl;
}

void node::insert(void)
{
    if (is_leaf)
    {
        is_leaf = false;

        northWest = new node(x-dx/4.0, y+dy/4.0, dx/2.0, dy/2.0, level*10+0, level+1);
        southWest = new node(x-dx/4.0, y-dy/4.0, dx/2.0, dy/2.0, level*10+1, level+1);
        northEast = new node(x+dx/4.0, y+dy/4.0, dx/2.0, dy/2.0, level*10+2, level+1);
        southEast = new node(x+dx/4.0, y-dy/4.0, dx/2.0, dy/2.0, level*10+3, level+1);
    }
    else
    {
        std::cout << "Node is not a leaf. Cannot create all four children.\n";
        return;
    }
}

void node::refine(void)
{
    // Refines all children for a given node recursively
    // Prevent excessive refinement (refinement creates 4^(max_level) nodes which can cause segfaults)
    if (!is_leaf)
    {
        std::cout << "Node is not a leaf. Cannot create all four children.\n";
        return;
    }
    else 
    {
        if (this->level >= node::max_level)
        {
            std::cout << "Exceeded " << node::max_level << " levels of refinement. Exiting...\n";
            return;
        }
        else
        {
            // Node will now have children, so it is no longer a leaf
            is_leaf = false;

            northWest = new node(x-dx/4.0, y+dy/4.0, dx/2.0, dy/2.0, level*10+0, level+1);
            northWest->printNode();
            northWest->refine();

            southWest = new node(x-dx/4.0, y-dy/4.0, dx/2.0, dy/2.0, level*10+1, level+1);
            southWest->printNode();
            southWest->refine();

            northEast = new node(x+dx/4.0, y+dy/4.0, dx/2.0, dy/2.0, level*10+2, level+1);
            northEast->printNode();
            northEast->refine();

            southEast = new node(x+dx/4.0, y-dy/4.0, dx/2.0, dy/2.0, level*10+3, level+1);
            southEast->printNode();
            southEast->refine();
        }
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

    if (northWest != NULL)
    {
        northWest->recurseTree(pointfile);
    }
    if (southWest != NULL)
    {
        southWest->recurseTree(pointfile);
    }
    if (northEast != NULL)
    {
        northEast->recurseTree(pointfile);
    }
    if (southEast != NULL)
    {
        southEast->recurseTree(pointfile);
    } 
    else
    {
        return;
    }
}

node *node::refinePoint(float p_x, float p_y) 
{
    // Tests the input point and allocates a new child node in the quadrant
    // in which the point is located
    //else
    {
        // Detect if the point is in the west half of the node
        if (p_x <= x)
        {
	        std::cout << "Point is in West half\n";

	        // Detect if the point is in the Northwest or Southwest quadrant
	        if (p_y >= y)
	        {
        	    // refine northwest 
                std::cout << "Point is in the Northwest corner\n";
                if (is_leaf == true)
                {
                    is_leaf = false;
                }
    	        if (northWest == NULL)
                {
    	            
                    is_leaf = false;
                    northWest = new node(x-dx/4.0, y+dy/4.0, dx/2.0, dy/2.0, level*10+0, level+1);
    	            return northWest;
                }
                else 
                {
                    std::cout << "Child already exists. Traversing one level...\n";
                    return northWest;
                }
        	}
    	    else
    	    {
    	        // refine southwest
                std::cout << "Point is in the Southwest corner\n";
    	        is_leaf = false;
                southWest = new node(x-dx/4.0, y-dy/4.0, dx/2.0, dy/2.0, level*10+1, level+1);
    	        return southWest;
    	    }
        }
        else
        {
            std::cout << "Point is in the East half.\n";
            if (p_y >= y)
	        {
	            // refine northeast
                std::cout << "Point is in the Northeast corner\n";
	            is_leaf = false;
                northEast = new node(x+dx/4.0, y+dy/4.0, dx/2.0, dy/2.0, level*10+2, level+1);
	            return northEast;
	        }
	        else
	        {
                // refine southeast
                std::cout << "Point is in the Southeast corner\n";
	            is_leaf = false;
                southEast = new node(x+dx/4.0, y-dy/4.0, dx/2.0, dy/2.0, level*10+3, level+1);
	            return southEast;
	        }
        }
    }
}

void node::refinePointWrapper()
{
    std::string fname3 = "pc_refinePointWrapper.dat";
 
    node *tempPtr3 = this;

    while (tempPtr3->level < 5)
    {
        tempPtr3 = (*tempPtr3).refinePoint(1.01, 3.013);
        tempPtr3->printNode();
        std::cout << "Level: " << tempPtr3->level << std::endl;
    }
    
    this->traverseTree(fname3);
}
