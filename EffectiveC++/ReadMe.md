https://stackoverflow.com/questions/6264249/how-does-the-compilation-linking-process-work
https://wizardforcel.gitbooks.io/100-gcc-tips/content/

## chp1. Acustoming Yourself to C++

### Item 1: View C++ as a federation of languages

### Item 2: Prefere consts, enums, and inlines to #defines

***Prefer compiler to the preprocessor***
https://en.wikipedia.org/wiki/C_preprocessor

1. Constant pointers (usually put in header files)

   ```cpp
   const char* const authorName = "Bella";
   ```

2. Class-specific constants

   For simple constants, prefer const objects or enums to #defines

   ```cpp
   class GamePlayer{
   private:
       // enum hack:
       // for compilers that do not accept in-class static const
       // like #define, you can never take address of enum, because they are just symbols
       // good compilers will never set storage for const integral types
       // fundamental technique of template metaprogramming
       // enum{NumTurns = 5};
       static const int NumTurns = 5; // constant declaration, may need to define it in source file
       int scores[NumTurns];
       static const double MaxScores; // in-class intialization is allowed only for integral types and only for constants
   };
   const double GamePlayer::MaxScores = 100.0;
   ```

   For function-like macros, prefer inline functions to #defines

### Item 3: Use const whenever possible

#### std::iterator behaves like raw pointer

```cpp
    char greeting[] = "hello";
    char *p0 = greeting;             // non-constant pointer, non-constant data
    const char *p1 = greeting;       // non-constant pointer, const data
    char *const p2 = greeting;       // constant pointer, non-constant data
    const char *const p3 = greeting; // constant pointer, constant data

    // STL iterator acts like raw_pointer
    int a[] = {0, 1, 2};
    std::vector<int> vec(a, a + 3);
    // the iterator/pointer itself cannot be changed
    // but the content it points to can be modified
    const std::vector<int>::iterator iter = vec.begin(); // T* const;
    *iter = 10;
    // ++iter; // error!!! iter is constant

    // the iterator can be changed, but the content it points cannot be changed
    std::vector<int>::const_iterator citer = vec.begin(); // const T*;
    ++citer;
    // *citer = 10; // error!!! *cIter is const
```

#### Make user-defined type behaves like built-in types

```cpp
class Rational{};
const Rational operator*(const Rational &a, const Rational &b);

Rational a(10), b(5), c(50);
if (a *b = c) // error!!! not compile. prevent programmer from writing == (comparison) to = (assignment)
```

#### const Member Functions (on constant object)

1. Bit constness vs Logical Constness

   ***Bit(Compiler) Constness*** Constant member function isn't allowed to modify any of non-static data member.

   ***Logical Constantness*** Avoid changing non-static data member in user-detected way.

   ```cpp
    class TextBlockV1
    {
    public:
        // const mem_fun
        const char &operator[](int pos) const
        {
            // do bounds checking
            // log access data
            // verify data integrity
            return text[pos];
        }

        // char &operator[](int pos)
        // {
        //     // do bounds checking
        //     // log access data
        //     // verify data integrity
        //     return text[pos];
        // }
        char &operator[](int pos)
        {
            return const_cast<char &>( // cast away constness of return-type for const mem_fun
                static_cast<const TextBlockV1 &>(*this)[pos]
                // cast *this to const and call const mem_fun,
                // also avoiding end-less recursion if invoking on non-constant member
            );
        }

    private:
        std::string text;
    };
   ```

2. Avoid code duplication by asking non-constant member function call const member function, ***!!!not vice versa***

   ***not vice versa*** Becauase, calling const mem_fun means not modifying data member, this will risk modifying data member in non-detected way.

   ```cpp
        class TextBlockV1
        {
        public:
            // const mem_fun
            const char &operator[](int pos) const
            {
                // do bounds checking
                // log access data
                // verify data integrity
                return text[pos];
            }

            // char &operator[](int pos)
            // {
            //     // do bounds checking
            //     // log access data
            //     // verify data integrity
            //     return text[pos];
            // }
            char &operator[](int pos)
            {
                return const_cast<char &>( // cast away constness of return-type for const mem_fun
                    static_cast<const TextBlockV1 &>(*this)[pos]
                    // cast *this to const and call const mem_fun,
                    // also avoiding end-less recursion if invoking on non-constant member
                );
            }

        private:
            std::string text;
        };
   ```

### Item 4. Make sure that objects are initialized before they're used

1. Mannually initialize objects of built-in type, because C++ only sometimes initalize external/static variables.
2. Use member initialize list instead of assignment inside constructor.

   Make sure all constructors initialize everything in the object.
   Base classes are initialized before derived classes.
   Within a class, data members are initialized in the order which they are declared.
   To avoid bugs, list members in initailization list in the same order they're declared in the class.

3. Avoid intialization order problems across translation units by replacing non-static objects with local static objects.

```cpp
class FileSystem{};
FileSystem& tfs(){
    static FileSystem fs;
    return fs;
}
class Directory{
    Directory(){
        size_t disks = tfs().numDisks(); // this ensures fs is initialized before being used
    }
};
Directory& dir(){
    static Directory direc;
    return direc;
}

```

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

### Item 9. Never call virtual functions during construction or deconstruction

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
```cpp
std::shared_ptr<Investment> pInv(createInvestment());
```
### Item 14: Think carefully about copying behavior in resource-managing classes

1. Prohibit copying
2. Reference-count the underlying resouces
3. Deep copy
4. Resouces ownership transfer

### Item 15: Provide access to raw resources in resource-managing classes

```cpp
Investment* rawPtr = pInv.get();
```
1. APIs often requires access to raw resources, so each RAII class should offer a way to get resources it manages.
2. Access maybe via explicit conversion or implicit conversion. Explicit conversion is safer. Implicit conversion is more convenient.

```cpp
void changeFontSize(FontHandle f, int newSize);
Font f;
int newFontSize;
...
changeFontSize(f.get(), newFontSize); // explicit conversion

class Font{
public:
    operator FontHandle()const{ // Implicit Conversion
        return f;
    }
};
```

### Item 16: Use the same form in corresponding uses of new and delete

1. new-delete
2. new a[]---delete []a

### Item 17: Store newed objects in smart pointers in standalone statements
```cpp
std::shared_ptr<Widget> pw(new Widget);
processWidget(pw, priority());
// !!!! never do this
// processWidget(std::shared_ptr<Widget>(new Widget), priority());
// because: compiler may new Widget-->priority()-->shared_ptr(), 
// exception may occur from the time a resource is created to the time the resouce is handled to a resource manager,
// in this case, call to priority()
```

## chp4. Design and Declarations

### Item 18: Make interfaces easy to use correctly and hard to use incorrectly

### Item 19: Treat class design as type design

### Item 20: Prefer pass-by-reference-to-const to pass-by-value

1. Prefer pass-by-reference-to-constant over pass-by-value, it is typically more efficient and avoids slicing problem.
2. For built-in types, STL iterators and STL function objects, pass-by-value is more appropriate.

### Item 21: Don't try to return a reference when you must return an object

### Item 22: Declare data members private

1. Declare data members private. It gives clients syntactically uniform access to data, affords fine-grained access control,
allows invariants to be enforced, and offers class authors implementation flexibility.

2. ***protected*** is no more encapsulated than ***public***. Both will induces unknown amount client code to be changed if the data member is changed.

### Item 23: Prefer non-member non-friend functions to member functions

Increase encapsulation, package flexibility and functional extensibility.

```cpp
// header "webbrowser.h"
namespace WebBrowserStuff{
    class WebBrowser{};
}
// header "webbrowserbookmarks.h"
namespace WebBrowserStuff{
// bookmark-related convenience functions
};
// header "webbrowsercookies.h"
namespace WebBrowserStuff{
// cookie-related convenience functions
};
```

### Item 24: Declare non-member functions when type conversions should apply to all parameters (Item 46)

```cpp
class Rational{
public:
    Rational(int numerator=0, int denominator=1):m_numerator(numerator), m_denominator(denominator){}
    int numerator(){return m_numerator;}
    int denominator(){return m_denominator;}
private:
    int m_numerator;
    int m_denominator;
}

const Rational operator*(const Rational& lhs, const Rational& rhs){
    return Rational(lhs.numerator()*rhs.numerator(), lhs.denominator()*rhs.denominator());
}

Rational oneFourth(1, 4);
Rational result;
result = oneFourth * 2; // Implicit conversion Rational(2, 1)
result = 2 * oneFourth; // Implicit conversion Rational(2, 1)
```

### Item 25: Consider support for a non-throwing swap

```cpp
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
```

## chp5. implementations

### Item 26: Postphone variable definitions as long as possible

```cpp
const int MINIMUM_PSWD_LEN = 10;

void encrypt(std::string &pwd) {}

std::string encrypt_password(const std::string &password)
{
    if (password.size() < MINIMUM_PSWD_LEN)
    {
        throw std::logic_error("Password is too short");
    }
    // try to postphone definiton until you have initialization arguments for it
    std::string encrypted(password);
    encrypt(encrypted);
    return encrypted;
}
```

Better encapsulation, might not efficient if construction and deconstruction is expensive.

```cpp
// cost: n construction + n deconstruction
for(...i){
    Widget w(i)
}
```

Efficient if assignment is cheap but not encapsulated well.

```cpp
// cost: 1 construction + 1 deconstruction + n assignment
Widget w;
for(...i){
   w = i;
}
```

### Item 27:  Minimize casting

#### old-style

1. (T)expression
2. T(expression)

#### C++ style

1. `const_cast<T>(expression)`: cast_away the constantness of objects.
2. `dynamic_cast<T>(expression)`: determine whether an object is of a particular type in an hierarchy, has significant run-time cost.
3. `reinterpret_cast<T>(expression)`: low-level cast that yields implementation dependent results, eg., casting a pointer to an int.
4. `static_cast<T>(expression)`: non-const to const, int to double, void* to typed pointers, pointer-to-base to pointer-to-derived.

```cpp
class Window{
    virtual void onResize(){}
};

class SpecialWindow: public Window{
    virtual void onResize(){
        Window::onResize();
        //... some stuff of SepcialWindow
    }
};
```

***replace dynamic_cast with type-safe containers or moving virtual function up the hierarchy, never do cascading dynamic_casts***

```cpp
typedef vector<shared_ptr<Window>> VWP;
VWP wptrs;
for(VWP::iterator it=wptrs.begin(); it!=wptrs.end(); ++it){
    if(SpecialWindow *psw=dynamic_cast<SpecialWindow>(it->get())){ // don't do this
        psw->blink(); 
    }
}
// declare type-safe containers: vector<shared_ptr<SpecialWindow>> wptrs;
// declare virtual blink() both on class Window and class SpecialWindow
```

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