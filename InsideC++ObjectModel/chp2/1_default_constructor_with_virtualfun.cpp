#include <iostream>
using namespace std;

class Widget
{
public:
    // virtual void flip() const = 0;
    void flip() const;
};

class Bell : public Widget
{
public:
    // virtual void flip() const
    // {
    //     cout << "Bell" << endl;
    // }
    void flip() const
    {
        cout << "Bell" << endl;
    }
};

class Whistle : public Widget
{
public:
    // virtual void flip() const
    // {
    //     cout << "Whistle" << endl;
    // }
    void flip() const
    {
        cout << "Whistle" << endl;
    }
};

void flip(const Widget &widget) { widget.flip(); } // compiler write this: (*widget.vptr[1])(&widget)

void foo()
{
    Bell b;
    Whistle w;

    flip(b);
    flip(w);
}

int main()
{
    foo();
    return 0;
}
