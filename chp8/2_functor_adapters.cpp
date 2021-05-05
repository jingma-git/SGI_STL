#include <vector>
#include <iostream>
#include <iterator>
#include <functional>
#include <algorithm>

using namespace std;

ostream_iterator<int> outite(cout, " ");
int ia[6] = {2, 21, 12, 7, 19, 23};
vector<int> iv(ia, ia + 6);

void test_bind()
{
    // (x+2)*3
    // for_each is non-mutating
    for_each(iv.begin(), iv.end(), bind2nd(multiplies<int>(), 3));
    copy(iv.begin(), iv.end(), outite);
    cout << endl;

    transform(iv.begin(), iv.end(), outite, bind2nd(multiplies<int>(), 3));
    cout << endl;
}

void print(int i) // To be used in STL
{
    cout << i << ' ';
}

class Int
{
public:
    explicit Int(int i) : m_i(i) {}
    void print1() const { cout << '[' << m_i << ']'; } // To be used in STL

private:
    int m_i;
};

void test_mem_fun_adapter()
{
    // count elements not less than 12
    cout << count_if(iv.begin(), iv.end(), not1(bind2nd(less<int>(), 12))) << endl; // 4
    transform(iv.begin(), iv.end(), outite, not1(bind2nd(less<int>(), 12)));
    cout << endl; // 0 1 1 0 1 1

    // function pointer and STL algo
    for_each(iv.begin(), iv.end(), print);
    cout << endl; // 2 21 12 7 19 23
    for_each(iv.begin(), iv.end(), ptr_fun(print));
    cout << endl; // 2 21 12 7 19 23

    // member function pointer and STL algo
    Int t1(3), t2(7), t3(20), t4(14), t5(68);
    vector<Int> Iv;
    Iv.push_back(t1);
    Iv.push_back(t2);
    Iv.push_back(t3);
    Iv.push_back(t4);
    Iv.push_back(t5);

    for_each(Iv.begin(), Iv.end(), mem_fun_ref(&Int::print1));
    cout << endl;
}

struct Shape
{
    virtual void display() = 0;
};

struct Rect : public Shape
{
    virtual void display() { cout << "Rect "; }
};

struct Circle : public Shape
{
    virtual void display() { cout << "Circle "; }
};

struct Square : public Rect
{
    virtual void display() { cout << "Square "; }
};

void test_mem_fun_adapter_polymorphism()
{
    vector<Shape *> c;
    c.push_back(new Rect);
    c.push_back(new Circle);
    c.push_back(new Square);

    for (int i = 0; i < c.size(); ++i)
    {
        c[i]->display();
    }
    cout << endl;

    for_each(c.begin(), c.end(), mem_fun(&Shape::display));
    cout << endl;
}
int main()
{
    // test_bind();
    // test_mem_fun_adapter();
    test_mem_fun_adapter_polymorphism();
    return 0;
}