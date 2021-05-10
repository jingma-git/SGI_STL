# The Semantics of Function

Three flavours of member functions:
1. non-static
2. static
3. virtual

## 4.1 Varieties of Member Invocation

1. non-static

   One C++ design criterion is that a nonstaic member function at a minimum must be as efficient as its analogous nonmember function.

   ```cpp
   float Point3d::magnitude()const{...}
   float magnitude(const Point3d* _this){...}
   ```

   **name mangling**: concatenate function name with argment types.

   ```cpp
   class Point
   {
       void x(float newX);
       float x();
   };

   // inside compiler
   class Point
   {
       void x_5PointFf(float newX);
       float x_5PointFv();
   }
   ```

2. virtual

   The invocation of a virtual member function through a class object should always be resolved by your compiler as an ordianry nonstastic member function.

3. static

   Static member functions, by being this-less and therefore of the same type as an equivalent nonmember function.

   ```cpp
   &Point3d::object_count();
   // yiels a value of type
   unsigned int (*)();
   // not of type
   unsigned int (Point3d::*)();
   ```

## 4.2 Virtual Member Functions

### Single Inheritance

Replace virtual function pointer for overrided virtual function in derived class's vtbl.

### Multiple Inheritance (MI)

Maintain one-to* vtbls, one for major Base class, the others for other base classes. Need to adjust *this when using other base class pointer.

### Virtual Inheritance (VI)

Maintain two vtbls, one for this class and record offset to virtual_base_class_table,  the other for virtual_base_class.

***!!! Never Never Never create a virtual base class with non-static data members. You will have serious trouble!!!***



## 4.3 Function Efficiency

Runtime: inline member function < (nonmember friend==static member==nonstatic member) < virtual member (indirected vptr searching) < vritual under multiple inheritance (adjust *this) < virtual under virtual inheritance (adjust *this).

***When your code is smaller than 8 lines, consider it to be an inline function. Since it will reduce runtime significantly.***


## 4.4 Pointer to Member Functions

***Static member functions, which are without a `this` pointer, are of type "pointer-to-function", not "pointer-to-member-function".***

In order to store pointer to virtual/virtul(MI)/virtual(VI), compiler need more complex processing or data_structure, eg. thunx.

## 4.5 Inline Functions

### Pros

1. Information hiding
2. Efficient function call

### Cons

Code bloat

1. Inline function are invoked many times. 
2. Arguments with side effects. 
3. Multiple calls within a single expression. 
4. Local variables inside inline function.