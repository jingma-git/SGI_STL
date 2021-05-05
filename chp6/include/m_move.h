#pragma once
#include <stdio.h>
namespace mj
{

    template <typename T>
    T &&move(T &val)
    {
        // printf("T& move\n");
        return static_cast<T &&>(val);
    }

    template <typename T>
    T &&move(T &&val)
    {
        // printf("T&& move\n");
        return static_cast<T &&>(val);
    }
}