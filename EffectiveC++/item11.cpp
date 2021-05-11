
class BitMap
{
};

class Widget
{
    void swap(Widget &rhs) // exchange *this's data and rhs's data, Item29
    {
    }

public:
    Widget &operator=(const Widget &rhs)
    {
        // handle both self-assignment and exception
        Widget temp(rhs); // make a copy of rhs's data
        swap(temp);       // swap *this's data with rhs
        return *this;
    }

private:
    BitMap *pb;
};

int main()
{
    return 0;
}