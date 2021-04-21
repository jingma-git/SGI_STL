#include <iostream>
using namespace std;

struct _list_node_base
{
    _list_node_base *prev;
    _list_node_base *next;
};

template <typename T>
struct _list_node : public _list_node_base
{
    T val;
};

template <typename T>
struct _list_iterator
{
    typedef _list_iterator<T> _Self;
    typedef T value_type;
    typedef T *pointer;
    typedef T &reference;

    reference operator*() const { return *_ptr; }

    pointer operator->() const { return _ptr; }

    _Self &operator++()
    {
        ptr = ptr->next;
        return *this;
    }

    _Self operator++(int)
    {
        _Self tmp = *this;
        ++(*this);
        return tmp;
    }

    bool operator==(const _list_iterator &i) const
    {
        return ptr == i._ptr;
    }

    bool operator!=(const _list_iterator &i) const
    {
        return ptr != i._ptr;
    }

    _list_node_base *_ptr;
};

template <typename T>
class list
{
public:
    typedef _list_iterator<T> iterator;
    //iterators
    iterator begin()
    {
    }

    iterator end()
    {
    }

    //capacity
    bool empty()
    {
    }

    size_t size()
    {
    }

    //modifiers
    iterator insert(iterator pos, const T &value)
    {
    }

    void push_front(const T &value)
    {
    }

    void pop_front(const T &value)
    {
    }

    void push_back(const T &value)
    {
    }

    void pop_back(const T &value)
    {
    }

private:
};

int main()
{
    list<int> l;
    for (int i = 0; i < 5; i++)
        l.push_back(i);
    // std::find(l.begin(), l.end(), 2);
    return 0;
}