#include <iostream>

namespace WidgetStuff
{
    class WidgetImpl
    {
    };

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
        WidgetImpl *pimpl; // pimpl (Pointer to implmentation) Idiom
    };

    inline void swap(Widget &a, Widget &b)
    {
        std::cout << "overloaded swap is called" << std::endl;
        a.swap(b);
    }
}

int main()
{
    using namespace WidgetStuff;
    Widget a, b;
    using std::swap;
    swap(a, b);
    return 0;
}