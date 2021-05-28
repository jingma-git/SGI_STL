// in application domain, composition means 'has-a' relationship
// in implemenetation domain, composition means 'is-a' relationship

#include <list>
#include <algorithm>
#include <iostream>
using namespace std;

template <typename T>
class MySet
{
public:
    typedef typename list<T>::iterator iterator;

    bool find(const T &val) const
    {
        return std::find(rep.begin(), rep.end(), val) != rep.end();
    }

    void insert(const T &val)
    {
        if (!find(val))
            rep.push_back(val);
    }

    void remove(const T &val)
    {
        if (find(val))
            rep.remove(val);
    }

    size_t size() const { return rep.size(); }

    iterator begin() { return rep.begin(); }

    iterator end() { return rep.end(); }

private:
    list<T> rep;
};

int main()
{
    MySet<int> s;
    s.insert(0);
    s.insert(0);
    s.insert(1);
    s.insert(2);
    s.insert(3);

    cout << "ini size=" << s.size() << endl;
    for (auto it = s.begin(); it != s.end(); ++it)
    {
        cout << *it << " ";
    }
    cout << endl;

    s.remove(1);
    cout << "after remove 1"
         << " size=" << s.size() << endl;
    for (auto it = s.begin(); it != s.end(); ++it)
    {
        cout << *it << " ";
    }
    cout << endl;
    return 0;
}