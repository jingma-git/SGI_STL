#include <stdio.h>

class Point
{
public:
    int x;
    int y;
    static int count;
};
int Point::count = 1;

int main()
{
    printf("&Point::count=%p, Point::count=%d\n", &Point::count, *(&Point::count));
    return 0;
}