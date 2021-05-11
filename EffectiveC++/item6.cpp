#include <iostream>

class Uncopy
{
protected:
    Uncopy() {} // allow construction and destruction of derived objects
    ~Uncopy() {}

private:
    Uncopy(const Uncopy &); // prevent copying
    Uncopy &operator=(const Uncopy &);
};

class HomeForSale : private Uncopy
{
public:
    HomeForSale() {}
};

int main()
{
    HomeForSale h0;
    HomeForSale h1(h0);  // cannot compile
    HomeForSale h2 = h0; // cannot compile
    return 0;
}