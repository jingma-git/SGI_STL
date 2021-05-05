## The C++ object model

non-static data member, and virtual table is in object <br>
static data member, non-static/static member functions is outside object <br>
virtual table maintain pointers to type_info and virtual functions

### class data members

1. static
2. non-static

### class member functions

1. static
2. non-static
3. virtual

## Keyword Distinction

struct vs class: struct in c++ provide interface to c

## Object Distinction

### Three Programming Diagram

1. procedural model in C
2. Abstract Data Type (ADT | Object-Based Model |OB Design)

   Users of abstraction are provided with a set of operations (**public interface**), whereas implementation remains hidden (**private implementation**).
3. Object-oriented Model (OO Design | **type extension**)

   **A collection of related types** are encapsulated through an abstract base class providing a common interface.

### The type of pointer

```cpp
ZooAnimal *px;
int *pi;
Array<String> *pa;
```

In terms of memory requirements, there is no difference. All three pointers above needs 4 bytes. However, the type of a pointer instructs the compiler as to how to interpret the memory found at a particular address and also how much memory that intepretation should span.

### Adding Polymorphism

Polymorphism encapsulates related types behind an abstract interface. The cost is an additional level of indirection, both in terms of memory acquisition and type resolution. C++ supports polymorphism through pointers.

OB design is faster in time and compact in memory layout. Faster because all function invocations are resolved at compile time and object construction need not set up virtual mechanism. Compact because each class object do not need carry additional overhead associated with virtual mechanism. However, OB Design is less flexible.