#include "m_alloc.h"
#include "m_def.h"

template <class T, class Alloc = mj::allocator<T>>
class vector
{
public:
    typedef T value_type;
    typedef T *pointer;
    typedef T &reference;
    typedef T *iterator;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;

protected:
    iterator start;          // current space
    iterator finish;         // current space
    iterator end_of_storage; // available space

    void insert_aux(iterator position, const T &x)
    {
    }

    void deallocate()
    {
    }

    void fill_initialize(size_type n, const T &value)
    {
    }
};