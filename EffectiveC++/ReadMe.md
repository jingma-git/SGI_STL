## chp1. Acustoming Yourself to C++

### Item 1: View C++ as a federation of languages

### Item 2: Prefere consts, enums, and inlines to #defines

### Item 3: Use const whenever possible

### Item 4. Make sure that objects are initialized before they're used

## chp2. Constructors, Deconstructors, and Assignment Operators

### Item 5. Know what functions C++ silently writes and calls

Public, non-virtual

1. Constructor
2. Copy constructor
3. Operator=
4. Deconstructor

### Item 6. Explicitly disallow the use of compiler-generated functions you do not want

```cpp
class Uncopy
{
protected:
    Uncopy() {} // allow construction and destruction of derived objects
    ~Uncopy() {}

private:
    Uncopy(const Uncopy &); // prevent copying
    Uncopy &operator=(const Uncopy &);
};

class HomeForSale : private Uncopy
{
public:
    HomeForSale() {}
};
```

### Item 7. Declare deconstructors virtual in polymorphic base classes (+)

Declaring all deconstructors virtual is just as wrong as never declaring them virtual. For a concrete class, declaring deconstructor virtual will increase the object's size and make them unaccessible from C language.

Declare a virtual destructor in a class and if and only if that class contains at least one virtual functions.

***Classes not designed to be base classes or not designed to be used polymorphically should not declare virtual destructors. All STL containers, std::string, std::inupt_iterator_tag, Uncopy(Item6)...***

### Item 8. Prevent exceptions from leaving deconstructors

```cpp
class DBConnection
{
public:
    static DBConnection create() {}
    void close() {} // close connection; throw an exception if closing fails
};

class DBConn
{
public:
    void close()
    {
        db.close(); // new function for client use
        closed = true;
    }

    ~DBConn()
    {
        if (!closed)
        {
            try
            {
                db.close();
            }
            catch (...)
            {
                // std::abort() // terminate program
                // swallow the exceptions
            }
        }
    }

private:
    DBConnection db;
    bool closed;
};
```

### Item 9. Never call virtual functions during construction or deconstruction ?

Don't call virtual functions during construction or deconstruction, because such calls will never go to a more derived class than that of the currrently executing constructor or deconstructor.

How to fix?

If you can't use virtual functions to call down from base classes during contruction, you can compensate by having derived classes pass information up to base class constructors.

### Item 10. Have operator= return a reference to *this

### Item 11:  Handle assignment to self in operator=

***copy and swap***

```cpp
class Widget{...};
Widget w;
w = w;

// handle self-assignment and ensure exception-safe
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
```

### Item 12: Copy all parts of an object

1. Copy all local data members
2. Invoke the appropriate copying function in all base classes.
## chp3. Resouce Management

### Item 13: Use objects to manage resources

### Item 14: Think carefully about copying behavior in resource-managing classes

### Item 15: Provide access to raw resources in resource-managing classes

### Item 16: Use the same form in corresponding uses of new and delete (OK)

### Item 17: Store newed objects in smart pointers in standalone statements

## chp4. Design and Declarations

### Item 18: Make interfaces easy to use correctly and hard to use incorrectly

### Item 19: Treat class design as type design

### Item 20: Prefer pass-by-reference to const to pass-by-value ?

### Item 21: Don't try to return a reference when you must return an object

### Item 22: Declare data members private

### Item 23: Prefer non-member non-friend functions to member functions ?

### Item 24: Declare non-member functions when type conversions should apply to all parameters ?

### Item 25: Consider support for a non-throwing swap

## chp5. implementations

### Item 26: Postphone variable definitions as long as possible

### Item 27:  Minimize casting (+)

### Item 28: Avoid returning "handles" to object internals

### Item 29: Strive for exception-safe code

### Item 30: Understand the ins and outs of inlining (!)

### Item 31: Minimize compilation dependencies between files

## chp6. Inheritance and Object-Oriented Design

### Item 32. Make sure public inheritance models "is-a"

### Item 33. Avoid hiding inherited names ?

### Item 34. Differentiate between inheritance of interface and inheritance of implementation

### Item 35. Consider alternatives to virtual functions

### Item 36. Never redefine an inherited non-virtual function (!)

? what the generated actualy looks like if I redefine a non-virtual member function

### Item 37. Never redefine a function's inherited default parameter value

### Item 38. Model "has a" or "is implemented in terms of" through  composition

### Item 39. Use private inheritance judiciously

### Item 40. Use multiple inheritance judiciously

## chp7. Templates and Generic Programming

### Item 41. Understand implicit interfaces and compile-time polymorphism ?

### Item 42. Understand the two meanings of typename

### Item 43. Know how to access names in templatized based classes ?

### Item 44. Factor parameter-independent code out of templates.

### Item 45. Use member function templates to accept "all compatible types"

### Item 46. Define non-member functions inside templates when type conversions are desired ?

### Item 47. Use traits classes for information about types

### Item 48. Be aware of template metaprogramming

## chp8. Customizing new and delete

### Item 49: Understand the behavior of the new-handler

### Item 50: Understand when it makes sense to replace new and delete ?

### Item 51: Adhere to convention when writing new and delete

### Item 52: Write placement delete if write placement new ?

## chp9. Miscellany

### Item 53: Pay attention to compiler warnings

### Item 54: Familarize yourself with STL

### Item 55: Familarize yourself with Boost