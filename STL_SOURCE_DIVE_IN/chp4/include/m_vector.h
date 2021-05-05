#include "m_alloc.h"
#include "m_uninitialized.h"
#include "m_construct.h"
#include "m_def.h"
#include "m_algo.h"
namespace mj
{
    template <class T, class Alloc = mj::allocator<T>>
    class vector
    {
    public:
        typedef T value_type;
        typedef T *pointer;
        typedef T &reference;
        typedef const T &const_reference;
        typedef T *iterator;
        typedef const T *const_iterator;
        typedef size_t size_type;
        typedef ptrdiff_t difference_type;

    protected:
        iterator start;          // current space
        iterator finish;         // current space
        iterator end_of_storage; // available space

        // called by push_back(val), insert(position, val)
        void insert_aux(iterator position, const T &x)
        {
            if (finish != end_of_storage)
            {
                construct(finish, *(finish - 1));
                ++finish;
                T x_copy = x;
                copy_backward(position, finish - 2, finish - 1);
                *position = x_copy;
            }
            else
            {
                const size_type old_size = size();
                const size_type len = old_size != 0 ? 2 * old_size : 1;

                iterator new_start = Alloc::allocate(len);
                iterator new_finish = new_start;
                try
                {
                    // copy start-position from old vector to new_start and on in new vector
                    new_finish = uninitialized_copy(start, position, new_start);
                    construct(new_finish, x);
                    ++new_finish;
                    // copy position-finish from old vector to new_finish=end_of_storage in new vector
                    new_finish = uninitialized_copy(position, finish, new_finish);
                }
                catch (...)
                {
                    destroy(new_start, new_finish);
                    Alloc::deallocate(new_start);
                    throw;
                }
                destroy(begin(), end());
                deallocate();

                start = new_start;
                finish = new_finish;
                end_of_storage = new_start + len;
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
        const_iterator begin() const { return start; }
        const_iterator end() const { return finish; }
        reference front() { return *start; }
        reference back() { return *(finish - 1); }
        size_type size() const { return size_type(end() - begin()); }
        size_type capacity() const { return size_type(end_of_storage - begin()); }
        bool empty() const { return begin() == end(); }
        reference operator[](size_type n) { return *(begin() + n); }

        vector() : start(0), finish(0), end_of_storage(0) {}
        vector(size_type n, const T &value) { fill_initialize(n, value); }
        vector(int n, const T &value) { fill_initialize(n, value); }
        vector(long n, const T &value) { fill_initialize(n, value); }
        vector(iterator first, iterator last)
        {
            size_type n = last - first;
            start = Alloc::allocate(n);
            end_of_storage = finish;
            finish = uninitialized_copy(first, last, start);
        }

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

        void pop_back()
        {
            --finish;
            destroy(finish);
        }

        iterator erase(iterator first, iterator last)
        {
            iterator i = mj::copy(last, finish, first);
            destroy(i, finish);
            finish = finish - (last - first);
            return first;
        }

        iterator erase(iterator position)
        {
            if (position != end())
            {
                copy(position + 1, finish, position);
                --finish;
                destroy(finish);
                return finish;
            }
        }

        void clear()
        {
            erase(begin(), end());
        }

        iterator insert(iterator position, size_type n, const T &x)
        {
            if (n != 0)
            {
                if (size_type(end_of_storage - finish) >= n) // space is available
                {
                    T x_copy = x;
                    const size_type elems_after = finish - position;
                    iterator old_finish = finish;
                    if (elems_after > n)
                    {
                        uninitialized_copy(finish - n, finish, finish);
                        finish += n;
                        copy_backward(position, old_finish - n, old_finish);
                        fill(position, position + n, x_copy);
                    }
                    else
                    {
                        uninitialized_fill_n(finish, n - elems_after, x_copy);
                        finish += n - elems_after;
                        uninitialized_copy(position, old_finish, finish);
                        finish += elems_after;
                        fill(position, old_finish, x_copy);
                    }
                }
                else
                {
                    const size_type old_size = size();
                    const size_type len = old_size + max(old_size, n);
                    iterator new_start = Alloc::allocate(len);
                    iterator new_finish = new_start;
                    try
                    {
                        new_finish = uninitialized_copy(start, position, new_start);
                        new_finish = uninitialized_fill_n(new_finish, n, x);
                        new_finish = uninitialized_copy(position, finish, new_finish);
                    }
                    catch (...)
                    {
                        destroy(new_start, new_finish);
                        Alloc::deallocate(new_start);
                        throw;
                    }
                    destroy(start, finish);
                    deallocate();
                    start = new_start;
                    finish = new_finish;
                    end_of_storage = new_start + len;
                }
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
