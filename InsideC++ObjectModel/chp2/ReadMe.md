# 2 The Semantics of Constructors
## virtual tables
https://pabloariasal.github.io/2017/06/10/understanding-virtual-tables/
https://davidlim2007.wordpress.com/page/2/

1. non-virtual member function: static dispatch, early binding at compile time
2. virtual member function: dynamic dispatch, dynamic binding at run time

## 2.1 Default Constructor Construction

### When will compiler implicitly write 'constructor' code for you?

1. Member class with default constructor
2. Base class with default constructor
3. Class with vritual function
4. Class with virtual base class

```cpp
// Member class with default constructor
class A{public: A(){}};
class B
{
public: 
    A a; 
    char* str;
}

// Base class with default constructor
class Base
{
    public: Base(){}
};

class Derived:public Base()
{
};

// Class with virtual function
// compiler do two things:
// 1. class vtbl is generated and populated with addresses of active virtual functions for that class.
// 2. within each class object, an additional pointer member __vptr is synthsized to hold the address of associated vtbl
class Widget
{
    virtual void flip()=0;   
}
class Dialog: public Widget
{
    virtual void flip(){}
}
class QOpenGLWidget: public Widget
{
    virtual void flip(){}
}
 
// Class with virtual base class
// For each distinct base class that is specified virtual, the most derived object contains only one base class subobject of that type, even if the class appears many times in the inheritance hierarchy
class B{public: int i;}
class X: public virtual B{public: int j;}
class Y: public virtual B{public: int k;}
class AA: public A, public B{public: int d;       }
```

### Common mistakes for new C++ programmer

1. A default constructor is synthesized for every class that does not define one.

   Only when one of above four situations happens compiler will write 'non-trivial constructor' for you. Classes that do not exhibit these characrteristics and that declare no default constructor are all said to have implicit, trivial default constructor. In practice, these trivial default constructor are not synthesized.

2. Compiler-synthesized default constructor provides explicit default initializers for each data member declared in class.

   Within the synthesized default constructor, only the base class subobjects and member class objects are initialized. All other nonstatic data members, such as integers, pointers... are not initialized. It is the programmer's job to provide it in class implementation.

## 2.2 Copy Constructor Construction

### When will compiler implicitly write 'copy constructor' code for you (Not Bitwise Copy Semantics?)

1. Member class with copy constructor existed (either explicitly specified by the programer or implicitly synthesized by the compiler)

2. Base class with copy constructor existed (explicitly declared or implicilty synthesized)

3. Class with virtual functions

4. Class with virtual base class

```cpp
class ZooAnimal
{
    virtual void draw(){}
};
class Bear: public ZooAnimal
{
    virtual void draw(){}
};

void draw(const ZooAnimal& zoey){zoey.draw();}

Bear yogi;
ZooAnimal franny = yogi; // slice happens, the synthesized copy constructor set franny's vptr to ZooAnimal's vtbl's address instead of Bear's vtbl address
draw(yogi); // invoke Bear::draw()
draw(franny); // invoke ZooAnimal::draw()

```