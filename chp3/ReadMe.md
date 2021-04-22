# Iterator
stl_iterator.h <br>
stl_iterator_base_types.h <br>
stl_iterator_base_funcs.h <br>
## Iterator esentially is Smart Pointer

1. de-reference: extract content: operator*()
2. member access: operator->()
3. forward_iterator: operator++(), operator++(int)
4. bidirectional_iterator: foward_iterator, operator--(), operator--(int)
5. randomaccess_iterator: ?

## traits: etract nested type from Iterator/Raw Pointer
stl_iterator_base_types.h
### Five nested type
```
template <typename I> //I: Iterator
struct iterator_traits{
    typedef typename I::difference_type difference_type;
    typedef typename I::iterator_category iterator_category;
    typedef typename I::value_type value_type;
    typedef typename I::pointer pointer;
    typedef typename I::reference reference;
}
```

### template partial specialization
make template suits both user-defined type but also raw-data type, expand suitability...
```
// partial specialization to support raw pointer
template <typename T>
struct iterator_traits<T *>
{
    typedef random_access_iterator_tag iterator_category;
    typedef T value_type;
    typedef ptrdiff_t difference_type;
    typedef T *pointer;
    typedef T &reference;
};
```

## travelsal strategy: Concept and Refinement
stl_iterator_base_funcs.h
### Five iterator category
```
///  Marking input iterators.
struct input_iterator_tag // read-only
{
};

///  Marking output iterators.
struct output_iterator_tag // write-only
{
};

/// Forward iterators support a superset of input iterator operations.
struct forward_iterator_tag : public input_iterator_tag
{
};

/// Bidirectional iterators support a superset of forward iterator
/// operations.
struct bidirectional_iterator_tag : public forward_iterator_tag
{
};

/// Random-access iterators support a superset of bidirectional
/// iterator operations.
struct random_access_iterator_tag : public bidirectional_iterator_tag
{
};
```
