#pragma once

namespace mj
{
    template <typename T>
    class allocator
    {
    public:
        static T *allocate(size_t n = 1)
        {
            return static_cast<T *>(::operator new(n * sizeof(T)));
        }

        static void deallocate(T *pointer, size_t n = 1)
        {
            ::operator delete(pointer);
        }

        static void construct(T *pointer, const T &val)
        {
            new (pointer) T(val);
        }

        static void destroy(T *pointer)
        {
            pointer->~T();
        }
    };
};