#pragma once

namespace mj
{
    template <class ForwardIterator, class T>
    void fill(ForwardIterator first, ForwardIterator last, const T &value)
    {
        for (; first != last; ++first)
            *first = value;
    }

    template <class OutputIterator, class Size, class T>
    OutputIterator fill_n(OutputIterator first, Size n, const T &value)
    {
        for (; n > 0; --n, ++first)
            *first = value;
        return first;
    }

}