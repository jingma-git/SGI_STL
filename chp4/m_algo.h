#pragma once
namespace mj
{
    template <class InputIter, class Function>
    Function for_each(InputIter first, InputIter last, Function f)
    {
        for (; first != last; ++first)
            f(*first);
        return f;
    }
}