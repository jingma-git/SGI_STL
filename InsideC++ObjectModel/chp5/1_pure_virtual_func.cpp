#include <iostream>
#include <cmath>
#include <vector>
using namespace std;
// https://www.artima.com/articles/pure-virtual-function-called-an-explanation

class AbstractShape
{
public:
    virtual double area() const = 0;
    double value() const
    {
        return area() * valuePerSquareUnit_;
    }
    // Meyers 3rd Item 7:
    virtual ~AbstractShape() {}

protected:
    AbstractShape(double valuePerSquareUnit) : valuePerSquareUnit_(valuePerSquareUnit) {}

private:
    double valuePerSquareUnit_;
};

class Rectangle : public AbstractShape
{
public:
    Rectangle(double width, double height, double valuePerSquareUnit)
        : width(width), height(height), AbstractShape(valuePerSquareUnit) {}

    virtual double area() const
    {
        return width * height;
    }
    // Meyers 3rd Item 7:
    virtual ~Rectangle() {}
    // ...
private:
    double width, height;
};

class Circle : public AbstractShape
{
public:
    Circle(double radius, double valuePerSquareUnit)
        : radius(radius), AbstractShape(valuePerSquareUnit) {}

    virtual double area() const
    {
        return M_PI * radius * radius;
    }
    // Meyers 3rd Item 7:
    virtual ~Circle() {}
    // ...
private:
    double radius;
};

int main()
{
    // This will not compile, even if there's a matching public constructor:
    // AbstractShape *p = new AbstractShape(value);
    {
        // Rectangle *pr = new Rectangle(2, 10, 1);
        // Circle *pc = new Circle(10, 1);

        // vector<AbstractShape *> shapes;
        // shapes.push_back(pr);
        // shapes.push_back(pc);
        // for (AbstractShape *s : shapes)
        // {
        //     cout << s->value() << endl;
        // }

        // delete pr;
        // delete pc;
    }

    AbstractShape *p1 = new Rectangle(2, 10, 1);
    std::cout << "value = " << p1->value() << std::endl;
    AbstractShape *p2 = p1; // Need another copy of the pointer.
    delete p1;
    std::cout << "now value = " << p2->value() << std::endl;
    return 0;
}