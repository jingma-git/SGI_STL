#include <iostream>
using namespace std;
// https://stackoverflow.com/questions/13065893/compare-a-pointer-to-member
class Point
{
public:
    virtual ~Point(){};
    int x;
    int y;
    int z;
    static int count;

    void func() {}
};

int Point::count = 0;

template <class class_type, class data_type1, class data_type2>
char *access_order(data_type1 class_type::*mem1, data_type2 class_type::*mem2)
{
    // return (mem1 < mem2 ? "mem1 first" : "mem2 first");
    // cannot compare function pointer in c++
    // https://stackoverflow.com/questions/1765431/c-comparing-member-function-pointers
    return "";
}

int main()
{
    // // access data member 's address in memory
    // Point p;
    // if (std::less<void *>()(&p.x, &p.y))
    //     cout << "x first" << endl;
    // else
    //     cout << "y first" << endl;

    // access data member's offset
    printf("x=%p\n", &Point::x); // 8
    printf("y=%p\n", &Point::y); // 12
    printf("z=%p\n", &Point::z); // 16
    printf("func=%p\n", &Point::func);

    int Point::*p1 = 0;
    int Point::*p2 = &Point::x;
    if (p1 == p2)
    {
        printf("p1 and p2 contains the same value\n");
        printf("they must address the same member\n");
    }
    return 0;
}