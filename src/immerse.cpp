
#include <iostream>

int main () {

    // trivial two-dimensional n-gon

    int nGon = 4;
    float vertX[] = {2.0, 1.0, 4.0, 5.0};
    float vertY[] = {1.0, 3.0, 4.0, 2.0};
    
    int edgeList[] = {0, 1, 1, 2, 2, 3, 3, 0};

    // find dimensions for bounding box with O(n) search
    float xMin = vertX[0];
    for (int n = 1; n < nGon; n++) {
        if ( vertX[n] < xMin) {
	        xMin = vertX[n];
        }
    }
    std::cout << xMin << std::endl;

    float xMax = vertX[0];
    for (int n = 1; n < nGon; n++) {
        if ( vertX[n] > xMax) {
	        xMax = vertX[n];
        }
    }
    std::cout << xMax << std::endl;
    
    float yMin = vertY[0];
    for (int n = 1; n < nGon; n++) {
        if ( vertY[n] < yMin) {
	        yMin = vertY[n];
        }
    }
    std::cout << yMin << std::endl;

    float yMax = vertY[0];
    for (int n = 1; n < nGon; n++) {
        if ( vertY[n] > yMax) {
	        yMax = vertY[n];
        }
    }
    std::cout << yMax << std::endl;
}
