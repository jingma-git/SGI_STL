#include "src/Core.h"
#include <iostream>
using namespace std;

int main()
{
    Matrix<double, 3, 3> v;
    cout << v.RowsAtCompileTime << endl;
    cout << v.SizeAtCompileTime << endl;
    Matrix<double, Dynamic, 1> col;
    cout << col.SizeAtCompileTime << endl;
    cout << col.CoeffReadCost << endl;

    Matrix<std::complex<int>, 3, 3> cv;
    cout << cv.CoeffReadCost << endl;
    return 0;
}