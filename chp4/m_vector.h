#include "m_alloc.h"
#include "m_uninitialized.h"
#include "m_construct.h"
#include "m_def.h"

namespace mj
{
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
            if (finish != end_of_storage)
            {
            }
            else
            {
                const size_type old_size = size();
                const size_type len = old_size != 0 ? 2 * old_size : 1;

                iterator new_start = Alloc::allocate(len);
                iterator new_finish = new_start;
            }
        }

        void deallocate()
        {
            if (start)
                Alloc::deallocate(start);
        }

        void fill_initialize(size_type n, const T &value)
        {
            start = allocate_and_fill(n, value);
            finish = start + n;
            end_of_storage = finish;
        }

    public:
        iterator begin() { return start; }
        iterator end() { return finish; }
        size_type size() const { return size_type(end() - begin()); }
        size_type capacity() const { return size_type(end_of_storage - begin()); }
        bool empty() const { return begin() == end(); }
        reference operator[](size_type n) { return *(begin() + n); }

        vector() : start(0), finish(0), end_of_storage(0) {}
        vector(size_type n, const T &value) { fill_initialize(n, value); }
        vector(int n, const T &value) { fill_initialize(n, value); }
        vector(long n, const T &value) { fill_initialize(n, value); }
        explicit vector(size_type n) { fill_initialize(n, T()); }

        ~vector()
        {
            destroy(start, finish);
            Alloc::deallocate(start);
        }

        void push_back(const T &x)
        {
            if (finish != end_of_storage)
            {
                construct(finish, x);
                ++finish;
            }
            else
            {
                insert_aux(end(), x);
            }
        }

    protected:
        iterator allocate_and_fill(size_type n, const T &x)
        {
            iterator result = Alloc::allocate(n);
            uninitialized_fill_n(result, n, x);
            return result;
        }
    };
} // namespace mj
