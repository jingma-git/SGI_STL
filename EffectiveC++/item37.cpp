// never redefine inherited default parameter
// virtual func means dynamic bound
// default parameter means static bound

#include <iostream>
using namespace std;

class Shape
{
public:
    enum Color
    {
        RED,
        GREEN,
        BLUE
    };

    virtual void draw(Color color = RED) const
    {
        cout << "shape::draw(" << color << ")" << endl;
    }
};

class Rectange : public Shape
{
public:
    virtual void draw(Color color = GREEN) const // bad! redefine default parameter
    {
        cout << "rectange::draw(" << color << ")" << endl;
    }
};

int main()
{
    Shape *pr = new Rectange;
    pr->draw(); //expect to be "rectange::draw(GREEN)" but get "rectange::draw(RED)"
    Rectange *pr1 = new Rectange;
    pr1->draw();
    return 0;
}