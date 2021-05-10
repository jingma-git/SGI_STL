#include <iostream>
#include <string.h>
using namespace std;

struct Point3i
{
    int x, y, z;
    virtual void draw(){};
    Point3i()
    {
        // this will set __vptr to 0
        cout << "construtor sizeof(Point3i)=" << sizeof(Point3i) << endl;
        memset(this, 0, sizeof(Point3i));
    }

    Point3i(const Point3i &p)
    {
        cout << "copy constructor" << endl;
        memcpy(this, &p, sizeof(Point3i));
    }
};

int main()
{
    Point3i p0;
    p0.x = 1;
    p0.y = 2;
    p0.z = 3;
    Point3i p1(p0);

    cout << p0.x << ", " << p0.y << ", " << p0.z << endl;
    cout << p1.x << ", " << p1.y << ", " << p1.z << endl;
    return 0;
}