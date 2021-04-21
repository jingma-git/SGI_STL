#include <iostream>
using namespace std;

class NewHandlerHolder
{
public:
    explicit NewHandlerHolder(std::new_handler handler) : h(handler) {}
    ~NewHandlerHolder()
    {
        std::set_new_handler(h);
    }

private:
    std::new_handler h;
};

template <class T>
class NewHandlerSupport
{
public:
    NewHandlerSupport() { counter++; }

    static int num_instances() { return counter; }

    static std::new_handler set_new_handler(std::new_handler p) throw()
    {
        std::new_handler old_handler = currentHandler;
        currentHandler = p;
        return old_handler;
    }

    static void *operator new(std::size_t size)
    {
        // install new-handler
        cout << "operator new" << endl;
        NewHandlerHolder h(std::set_new_handler(currentHandler));
        return ::operator new(size);
    }

private:
    static std::new_handler currentHandler;
    static int counter;
};

template <class T>
std::new_handler NewHandlerSupport<T>::currentHandler = 0;

template <class T>
int NewHandlerSupport<T>::counter = 0;

class Widget : public NewHandlerSupport<Widget>
{
public:
private:
};

void out_of_mem()
{
    std::cerr << "Unable to statisfy request for memory\n";
    std::abort();
}
int main()
{
    Widget::set_new_handler(out_of_mem);
    Widget *pw1 = new Widget;
    Widget *pw2 = new Widget;
    cout << NewHandlerSupport<Widget>::num_instances() << endl;
    cout << NewHandlerSupport<int>::num_instances() << endl;
    return 0;
}