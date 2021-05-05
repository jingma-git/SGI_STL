#pragma once
#include "m_def.h"
#include <stdlib.h>
#include <stdio.h>

#if !defined(__THROW_BAD_ALLOC)
#define __THROW_BAD_ALLOC      \
    printf("out of memory\n"); \
    exit(1)
#endif
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

    class __malloc_alloc_template
    {
    private:
        static void *oom_malloc(size_t);
        static void *oom_realloc(void *, size_t);
        // function pointer to handle out of memory (oom)
        static void (*__malloc_alloc_oom_handler)();

    public:
        static void *allocate(size_t n)
        {
            void *result = malloc(n);
            if (0 == result)
                result = oom_malloc(n);
            return result;
        }

        static void deallocate(void *p, size_t n)
        {
            free(p);
        }

        static void *reallocate(void *p, size_t old_sz, size_t new_sz)
        {
            void *result = realloc(p, new_sz);
            if (0 == result)
                result = oom_realloc(p, new_sz);
            return result;
        }

        // simulate c++'s set_new_handler to handle oom
        static void (*set_malloc_handler(void (*f)()))()
        {
            void (*old)() = __malloc_alloc_oom_handler;
            __malloc_alloc_oom_handler = f;
            return (old);
        }
    };

    void (*__malloc_alloc_template::__malloc_alloc_oom_handler)() = 0;

    void *__malloc_alloc_template::oom_malloc(size_t n)
    {
        void (*my_malloc_handler)();
        void *result;
        for (;;) // continuosly try release, allocate, construct
        {
            my_malloc_handler = __malloc_alloc_oom_handler;
            if (0 == my_malloc_handler)
            {
                __THROW_BAD_ALLOC;
            }
            (*my_malloc_handler)(); // try to release memory
            result = malloc(n);     // allocate
            if (result)
                return result;
        }
    }

    void *__malloc_alloc_template::oom_realloc(void *p, size_t n)
    {
        void (*my_malloc_handler)();
        void *result;
        for (;;) // continuosly try release, allocate, construct
        {
            my_malloc_handler = __malloc_alloc_oom_handler;
            if (0 == my_malloc_handler)
            {
                __THROW_BAD_ALLOC;
            }
            (*my_malloc_handler)(); // try to release memory
            result = realloc(p, n); // allocate
            if (result)
                return result;
        }
    }

    typedef __malloc_alloc_template malloc_alloc;

    enum
    {
        __ALIGN = 8
    };

    enum
    {
        __MAX_BYTES = 128
    };

    enum
    {
        __NFREELISTS = __MAX_BYTES / __ALIGN
    };

    class __default_alloc_template
    {
        // private:
    public:
        // adjust bytes to multiple of 8
        static size_t ROUND_UP(size_t bytes)
        {
            return (bytes + __ALIGN - 1) & ~(__ALIGN - 1);
        }

        //  private:
        union obj
        {
            union obj *free_list_link;
            char client_data[1];
        };

        // private:
        // 16 freelists
        static obj *volatile free_list[__NFREELISTS]; // 128 bytes memory, __NFREELISTS == 16, each element takes 8 bytes

        static size_t FREELIST_INDEX(size_t bytes)
        {
            return ((bytes + __ALIGN - 1) / __ALIGN - 1);
        }

        static void *refill(size_t n)
        {
            // n: bytes for one chunk
            int nobjs = 20;
            char *chunk = chunk_alloc(n, nobjs);
            obj *volatile *my_free_list;
            obj *result;
            obj *current_obj, *next_obj;
            int i;
            if (1 == nobjs)
                return chunk;
            my_free_list = free_list + FREELIST_INDEX(n);
            result = (obj *)chunk;
            *my_free_list = next_obj = (obj *)(chunk + n); // next node in free_list
            // link node in free list
            for (i = 1;; i++)
            {
                current_obj = next_obj;
                next_obj = (obj *)((char *)next_obj + n);
                if (nobjs - 1 == i)
                {
                    current_obj->free_list_link = 0;
                    break;
                }
                else
                {
                    current_obj->free_list_link = next_obj;
                }
            }
            return result;
        }

        // allocate nobjs of memory chunk from memory pool
        static char *chunk_alloc(size_t size, int &nobjs)
        {
            printf("chunk=%ld bytes, nobjs=%d, heap_size=%ld\n", size, nobjs, heap_size);
            char *result;
            size_t total_bytes = size * nobjs;
            size_t bytes_left = end_free - start_free;

            if (bytes_left >= total_bytes)
            {
                printf("bytes_left(%ld) >= total_bytes(%ld)\n", bytes_left, total_bytes);
                result = start_free;
                start_free += total_bytes;
                return result;
            }
            else if (bytes_left >= size)
            {
                // the remaining space in memory pool is not enough for user-need
                // but is enough for at least one chunk
                printf("bytes_left(%ld) >= size(%ld)\n", bytes_left, size);
                nobjs = bytes_left / size;
                total_bytes = size * nobjs;
                result = start_free;
                start_free += total_bytes;
                return result;
            }
            else
            {
                // the remaining space is not enough for one chunk
                size_t bytes_to_get = 2 * total_bytes + ROUND_UP(heap_size >> 4);
                printf("no space left in mempool, bytes_to_get=%ld\n", bytes_to_get);
                if (bytes_left > 0)
                {
                    obj *volatile *my_free_list = free_list + FREELIST_INDEX(bytes_left);
                    // add the remainning space to free list
                    ((obj *)start_free)->free_list_link = *my_free_list;
                    *my_free_list = (obj *)start_free;
                }
                start_free = (char *)malloc(bytes_to_get);
                if (start_free == 0)
                {
                    // not enough space in heap
                    // try search whether there still exists some space in free_list(mempool)
                    int i;
                    obj *volatile *my_free_list, *p;
                    for (i = size; i <= __MAX_BYTES; i += __ALIGN)
                    {
                        my_free_list = free_list + FREELIST_INDEX(i);
                        p = *my_free_list;
                        if (0 != p)
                        {
                            *my_free_list = p->free_list_link;
                            start_free = (char *)p;
                            end_free = start_free + i;
                            return chunk_alloc(size, nobjs);
                        }
                    }
                    end_free = 0; // oops! there really no extra free space
                    start_free = (char *)malloc_alloc::allocate(bytes_to_get);
                }
                heap_size += bytes_to_get;
                end_free = start_free + bytes_to_get;
                return chunk_alloc(size, nobjs);
            }
        }

        // chunk allocation state
        static char *start_free; // called by chunk alloc
        static char *end_free;   // called by chunk alloc
        static size_t heap_size;

    public:
        static void *allocate(size_t n)
        {
            obj *volatile *my_free_list;
            obj *result;
            if (n > (size_t)__MAX_BYTES)
            {
                return malloc_alloc::allocate(n);
            }

            my_free_list = free_list + FREELIST_INDEX(n);
            result = *my_free_list;
            if (result == 0)
            {
                void *r = refill(ROUND_UP(n));
                return r;
            }
            *my_free_list = result->free_list_link;
            return result;
        }

        static void deallocate(void *p, size_t n)
        {
            obj *q = (obj *)p;
            obj *volatile *my_free_list;

            if ((n > (size_t)__MAX_BYTES))
            {
                malloc_alloc::deallocate(p, n);
                return;
            }

            my_free_list = free_list + FREELIST_INDEX(n);
            q->free_list_link = *my_free_list; // recycle
            *my_free_list = q;
        }

        static void *reallocate(void *p, size_t old_sz, size_t new_sz) {}
    };

    char *__default_alloc_template::start_free = 0;
    char *__default_alloc_template::end_free = 0;
    size_t __default_alloc_template::heap_size = 0;
    __default_alloc_template::obj *volatile __default_alloc_template::free_list[__NFREELISTS] = {0, 0, 0, 0,
                                                                                                 0, 0, 0, 0,
                                                                                                 0, 0, 0, 0,
                                                                                                 0, 0, 0, 0};
    template <class T, class Alloc>
    class simple_alloc
    {
    public:
        static T *allocate(size_t n)
        {
            return 0 == n ? 0 : (T *)Alloc::allocate(n * sizeof(T));
        }

        static T *allocate(void)
        {
            return (T *)Alloc::allocate(sizeof(T));
        }

        static void deallocate(T *p, size_t n)
        {
            if (0 != n)
                Alloc::deallocate(p, n * sizeof(T));
        }

        static void deallocate(T *p)
        {
            Alloc::deallocate(p, sizeof(T));
        }
    };

    typedef malloc_alloc alloc;
};