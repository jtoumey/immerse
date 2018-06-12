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

#ifndef IMMERSE_H
#define IMMERSE_H

#include <iostream>
#include <vector>
#include <fstream>

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
    bool inBoundary(float, float);
};

#endif // IMMERSE_H