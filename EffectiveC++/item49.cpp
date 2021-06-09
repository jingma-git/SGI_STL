#include <iostream>
using namespace std;

class NewHandlerHolder
{
public:
    explicit NewHandlerHolder(std::new_handler nh) : handler(nh) {}
    ~NewHandlerHolder()
    {
        std::set_new_handler(handler);
    }

private:
    std::new_handler handler;
    NewHandlerHolder(const NewHandlerHolder &);
    NewHandlerHolder &operator=(const NewHandlerHolder &);
};

template <typename T>
class NewHandlerSupport
{
public:
    static std::new_handler set_new_handler(std::new_handler p) throw();
    static void *operator new(std::size_t size) throw(std::bad_alloc);

private:
    static std::new_handler currentHandler;
};

template <typename T>
std::new_handler NewHandlerSupport<T>::set_new_handler(std::new_handler p) throw()
{
    std::new_handler old_handler = currentHandler;
    currentHandler = p;
    return old_handler;
}

template <typename T>
void *NewHandlerSupport<T>::operator new(std::size_t size) throw(std::bad_alloc)
{
    cout << "operator new: " << size << endl;
    NewHandlerHolder h(std::set_new_handler(currentHandler));
    return ::operator new(size);
}

template <typename T>
std::new_handler NewHandlerSupport<T>::currentHandler = 0;

class Widget : public NewHandlerSupport<Widget>
{
    int a[1000000000000000];
};

void out_of_mem()
{
    std::cerr << "out_of_mem: mem alloc fails" << endl;
    std::abort();
}

int main()
{
    // cout << out_of_mem << endl;
    Widget::set_new_handler(out_of_mem);
    Widget *w = new Widget;
    return 0;
}