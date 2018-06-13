#include "nGon.h"

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