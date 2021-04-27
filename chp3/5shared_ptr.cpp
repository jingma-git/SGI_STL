#include <iostream>
#include <memory>
#include <vector>
using namespace std;

struct Base
{
    int x;
    Base(int x) : x(x) { cout << "Base::Base()\n"; }
    ~Base() { cout << "Base::~Base()\n"; }
};

struct Derived : public Base
{
    Derived(int x) : Base(x) { cout << "  Derived::Derived()\n"; }
    ~Derived() { cout << "  Derived::~Derived()\n"; }
};

typedef std::shared_ptr<Base> BPtr;
int main()
{
    std::shared_ptr<Base> p(new Derived(10));
    cout << p.get() << "-" << p->x << ", " << p.use_count() << endl;
    vector<BPtr> ptrs;
    ptrs.push_back(p);
    ptrs.push_back(p);
    for (int i = 0; i < ptrs.size(); i++)
    {
        cout << ptrs[i]->x << "| " << p.use_count() << endl;
    }
    ptrs[0]->x = 11;

    cout << "after change pointed value" << endl;
    for (int i = 0; i < ptrs.size(); i++)
    {
        cout << ptrs[i]->x << "| " << p.use_count() << endl;
    }
    return 0;
}