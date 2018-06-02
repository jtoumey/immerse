
#include <iostream>

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

    int nGon = 4;
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
}
