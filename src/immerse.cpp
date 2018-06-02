
#include <iostream>

int main () {

    // trivial two-dimensional n-gon

    int nGon = 4;
    float vertX[] = {2.0, 1.0, 4.0, 5.0};
    float vertY[] = {1.0, 3.0, 4.0, 2.0};
    float bBoxDx, bBoxDy;
   // float bBoxX[4];
   // float bBoxY[4];
    
    int edgeList[] = {0, 1, 1, 2, 2, 3, 3, 0};

    // find dimensions for bounding box with O(n) search
    float xMin = vertX[0];
    for (int n = 1; n < nGon; n++) {
        if ( vertX[n] < xMin) {
	        xMin = vertX[n];
        }
    }

    float xMax = vertX[0];
    for (int n = 1; n < nGon; n++) {
        if ( vertX[n] > xMax) {
	        xMax = vertX[n];
        }
    }
    
    float yMin = vertY[0];
    for (int n = 1; n < nGon; n++) {
        if ( vertY[n] < yMin) {
	        yMin = vertY[n];
        }
    }

    float yMax = vertY[0];
    for (int n = 1; n < nGon; n++) {
        if ( vertY[n] > yMax) {
	        yMax = vertY[n];
        }
    }

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
}
