#pragma once
namespace mj
{
    template <typename _Value>
    struct _Iter_equals_val
    {
        _Value &_M_value;

        explicit _Iter_equals_val(_Value &__value)
            : _M_value(__value)
        {
        }

        template <typename _Iterator>
        bool
        operator()(_Iterator __it)
        {
            return *__it == _M_value;
        }
    };

    template <typename _Value>
    inline _Iter_equals_val<_Value>
    __iter_equals_val(_Value &__val)
    {
        return _Iter_equals_val<_Value>(__val);
    }
} // namespace mj
