#ifndef NODE_H
#define NODE_H

#include <iostream>

class node {

public:   
    float x, y;
    float dx, dy;
    int data;
    int level;
    bool is_leaf;

    // Pointers to child nodes
    node *northWest;
    node *northEast;
    node *southWest;
    node *southEast;

    node (float _x, float _y, float _dx, float _dy, int _data, int _level) {
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
    node () {
        is_leaf = true;
        northWest = NULL;
        northEast = NULL;
        southWest = NULL;
        southEast = NULL;
    }
    void insert(void);
    void printNode(void);
    void printNode2(void);
    void refine(void);
    bool inBoundary(float, float);
    void traverseTree(void);
    void recurseTree(std::ostream&);
};

#endif // NODE_H
