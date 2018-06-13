#ifndef NGON_H
#define NGON_H

#include <vector>

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

#endif // NGON_H
