## new vs operator new(size_t n) && placement new
**new**: `A* a = new A`, call void* operator new(size_t) and then A's constructor <br>
**operator new**:  `void* operator new(size_t n)`, allocate space

```
A* ptr = static_cast<A*> operator new(5*sizeof(A)); // (1)
A* ptr = (A*)malloc(5*sizeof(A)); // has similar effects as (1)
```

**placement new**: `new (pointer) A()`,  call constructor and place content to space, is crucial to improve efficiency <br>
**operator delete**: `operator delete(void*)`, release space

```
operator delete(ptr); 
free(ptr);
```

## template
partial specialization only for class template

## traits and func(tag_type)
tag_type: input_iterator_tag, forward_iterator_tag ... __true_type, __false_type <br>
use traits and func(tag_type) to unditionally select which implementation to call

```
struct __true_type{};
struct __false_type{};

template <class T>
struct __type_traits{
    typedef __false_type is_POD_type;
};

template <> // explicit/full specilization
struct __type_traits<int>{
    typedef __true_type is_POD_type;
};

template <T> // partial specialization for raw pointer
struct __type_traits<T*>{
    typedef __true_type is_POD_type;
};

template <class _ForwardIter, class _Size, class _Tp, class _Tp1>
inline _ForwardIter
__uninitialized_fill_n(_ForwardIter __first, _Size __n, const _Tp &__x, _Tp1 *)
{
    typedef typename __type_traits<_Tp1>::is_POD_type _Is_POD;
    return __uninitialized_fill_n_aux(__first, __n, __x, _Is_POD());
}
```

## vector
allocate new space -> move elements from old space to new space -> deallocate old space

## deque
lists of individual dynamically allocated memory blocks (when user uses it, it seems a wholesome continous memory),
constant time access,
const-time insertion and deletion at both end,
linear-time insertion and deletion from middle

