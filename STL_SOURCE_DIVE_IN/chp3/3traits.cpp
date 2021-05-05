#include <iostream>

typedef long int ptrdiff_t;

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

template <class Category, class T, class Distance = ptrdiff_t, class Pointer = T *, class Reference = T &>
struct iterator
{
    typedef Category iterator_category;
    typedef T value_type;
    typedef Distance difference_type;
    typedef Pointer pointer;
    typedef Reference reference;
};

template <typename T>
struct MyIter
{
    typedef long int difference_type;
    typedef T value_type;
    typedef T *pointer;
    typedef T &reference;

    MyIter(T *ptr) : _ptr(ptr) {}

    reference operator*() const { return *_ptr; }

    pointer operator->() const { return _ptr; }

    T *_ptr;
};

template <class I>
typename I::value_type func(I iter)
{
    return *iter;
}

template <class I>
struct iterator_traits // describe/deduct Iterator's value_type
{
    typedef typename I::difference_type difference_type;
    typedef typename I::value_type value_type;
    typedef typename I::pointer pointer;
    typedef typename I::reference reference;
    typedef typename I::iterator_category iterator_category;
};

template <class T>
struct iterator_traits<T *> // partial specialization to deduct raw_pointer's value_type
{
    typedef T value_type;
    typedef T *pointer;
    typedef T &reference;
    typedef random_access_iterator_tag iterator_category;
    typedef long int difference_type;
};

// template <class T>
// struct iterator_traits<const T *> // partial specialization to deduct raw_pointer's value_type
// {
//     typedef T value_type;
// };

template <class I>
typename iterator_traits<I>::value_type func1(I iter)
{
    return *iter;
}

template <class I, class T>
typename iterator_traits<I>::difference_type count(I first, I last, const T &value)
{
    typename iterator_traits<I>::difference_type n = 0;
    for (; first != last; ++first)
        if (*first == value)
            ++n;
    return n;
}

template <class InputIterator, class Distance>
void _advance(InputIterator &i, Distance n, input_iterator_tag)
{
    while (n--)
        ++i;
}

template <class ForwardIterator, class Distance>
void _advance(ForwardIterator &i, Distance n, forward_iterator_tag)
{
    _advance(i, n, input_iterator_tag());
}

template <class BidirectionalIterator, class Distance>
void _advance(BidirectionalIterator &i, Distance n, bidirectional_iterator_tag)
{
    if (n >= 0)
        while (n--)
            ++i;
    else
        while (n++)
            --i;
}

template <class RandomAccessIterator, class Distance>
void _advance(RandomAccessIterator &i, Distance n, random_access_iterator_tag)
{
    i += n;
}

template <class InputIterator, class Distance>
void advance(InputIterator &i, Distance n)
{
    _advance(i, n, iterator_traits<InputIterator>::iterator_category());
}

#include <iostream>
using namespace std;
int main()
{
    MyIter<int> it(new int(10));
    cout << func(it) << endl;

    int *raw_ptr = new int(3);
    // cout << func(raw_ptr) << endl; // does not work since raw pointer does have nested value_type
    cout << func(it) << endl;
    cout << func1(raw_ptr) << endl;

    const int *craw_ptr = new int(1);
    cout << func1(craw_ptr) << endl;
    return 0;
}