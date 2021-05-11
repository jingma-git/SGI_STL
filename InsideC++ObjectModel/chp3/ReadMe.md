# The Semantics of Data

## Memory layout

```cpp
// 64-bit Ubuntu
// pointer's default memory takes 8 bytes
#include <iostream>
using namespace std;

struct X
{
};

struct Y : virtual public X
{
};

struct Z : virtual public X
{
};

struct A : public Y, public Z
{
};

int main()
{
    cout << "sizeof(X)=" << sizeof(X) << endl; // one char to store X object's memory address
    cout << "sizeof(Y)=" << sizeof(Y) << endl; // __vbc (virtual base class) to X
    cout << "sizeof(Z)=" << sizeof(Z) << endl; // __vbc to Y
    cout << "sizeof(A)=" << sizeof(A) << endl; // sizeof(Y) + sizeof(Z)

    // sizeof(X)=1
    // sizeof(Y)=8
    // sizeof(Z)=8
    // sizeof(A)=16
    return 0;
}
```

The C++ object model representation for nonstatic datamembers optimizes for space and access time to prevese compalibility with C struct by storing the members directly within each object. Static data members are maintained in the global segment of the program and do not affect the size of individual class objects. Only one instance of a static data member of a class exists within a program regardless of the number of times that class is an object of direct or indirect derivation. (The static data members of a template class behaves differently.)

## 3.1 The Binding of a Data Member

Place nested type declarations at the beginning of the class.

## 3.2 Data Member Layout

1. C++ standard requires that within an access section (private, public, protected section of a class declaration) later members have higher address.
2. Compiler synthesized __vptr traditionally has been placed after all explicitly declared class members.
3. Data members within multiple access sections are allowed to be placed freely.

## 3.3 Access of Data Member

### Static Data Members

Static data is stored out of class. No space or time overhead occurs.

### Nonstatic Data Members

Is the access of data member x significantly different when accessed through the object origin and the pointer pt?

```cpp
Point3d origin, *pt = &origin;
origin.x = 0.0;
pt->x = 0.0;
```

It is signficantly different when Point3d is a derived class containing a virtual base class in its inheritance hierarchy and x is an inherited member from that virtual base class. The resolution of the access must be delayed at runtime.

## 3.4 Inheritance and Data Member

### Concrete Inheritance

1. In most cases, the derived class has the same memory layout as C struct.
2. **Space cost** However, the derived class may takes more space due to alignment.
3. **Time cost** Access time is as fast as their 'single-composed' counterpart.

```cpp
// single-composed Point3d
struct Point3
{
    int x;
    int y;
    int z;
    Point3(int x_, int y_, int z_):x(x_), y(y_), z(z_){}
};

// derived Point3d
struct Point2
{
    int x;
    int y;
    Point2(int x_, int y_):x(x_), y(y_){}
};

struct Point3: public Point2
{
    int z;
    Point3(int x_, int y_, int z_):Point2(x_, y_), z(z_){}
};
```

### Single Inheritance with Virtual Functions

In Microsoft Compiler, place vptr at the start of the class, making it more efficient in invocating virtual functions.

### Multiple Inheritance

If place vptr at the start of class, to access member, we need add an offset.

### Inheritance with Virtual Base Class

The most effective design: an virtual base class without any data members. Otherwise, compiler must figure out ways to access this data member, either through virtual base class table (Microsoft Compiler) or through virtual_base_class_offset (Bjarne).

