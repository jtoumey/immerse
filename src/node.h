#ifndef NODE_H
#define NODE_H

#include <iostream>

class node {

//public:
private:
    // node center
    float x, y;
    float dx, dy;
    int data;
    int level;

    // Static maximum level of refinement
    static int max_level;

    /* 
     *  Static flag for printing to file
     */
    static bool print_flag;
    
    bool is_leaf;


    // Pointers to child nodes
    node *northWest;
    node *northEast;
    node *southWest;
    node *southEast;

public:
    // Constructors: Default and for during a refinement/insert operation
    node ();
    node (float _x, float _y, float _dx, float _dy, int _data, int _level);

    // Member functions
    void insert(void);
    void printNode(void);
    void refine(void);
    bool inBoundary(float, float);
    void traverseTree(const std::string&);
    void recurseTree(std::ostream&);
    node * refinePoint(float, float);
    void refinePointWrapper(void);
};

#endif // NODE_H
