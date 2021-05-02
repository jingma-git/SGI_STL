#include "m_memory.h"

static size_t ROUND_UP(size_t bytes)
{
    return (bytes + 8 - 1) & ~(8 - 1);
}

static size_t FREELIST_INDEX(size_t bytes)
{
    return ((bytes + 8 - 1) / 8 - 1);
}

int main()
{
    {
        // mj::__malloc_alloc_template alloc;
        // alloc.allocate(10000000000000000);
    }

    {
        // for (size_t i = 0; i < 100; ++i)
        // {
        //     printf("%ld %ld\n", i, ROUND_UP(i));
        // }
    }

    {
        // for (size_t i = 0; i < 137; ++i)
        // {
        //     printf("%ld %ld\n", i, FREELIST_INDEX(i));
        // }
    }

    {
        // mj::__default_alloc_template allocator;
        // allocator.allocate(96);
    }

    {
        // mj::__default_alloc_template allocator;
        // int nobjs = 20;
        // allocator.chunk_alloc(32, nobjs);
        // nobjs = 20;
        // allocator.chunk_alloc(64, nobjs);
        // nobjs = 20;
        // allocator.chunk_alloc(96, nobjs);
    }

    {
        mj::__default_alloc_template allocator;
        void *ptr = allocator.allocate(32);
        void *ptr1 = allocator.allocate(64);
        allocator.deallocate(ptr, 32);
        allocator.deallocate(ptr1, 64);
    }
    return 0;
}