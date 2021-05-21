#include <iostream>

namespace WidgetStuff
{
    template <typename T>
    class WidgetImpl
    {
    };

    template <typename T>
    class Widget
    {
    public:
        void swap(Widget &other)
        {
            std::cout << "member swap is called" << std::endl;
            using std::swap;
            swap(pimpl, other.pimpl);
        }

    private:
        WidgetImpl<T> *pimpl; // pimpl (Pointer to implmentation) Idiom
    };

    template <typename T>
    inline void swap(Widget<T> &a, Widget<T> &b) // overload std::swap
    {
        std::cout << "overloaded swap is called" << std::endl;
        a.swap(b);
    }
}

int main()
{
    using namespace WidgetStuff;
    Widget<int> a, b;
    using std::swap; // when calling swap, employ a 'using' declaration for std::swap
    swap(a, b);      // then calll swap without namespace qualificaiton
    return 0;
}