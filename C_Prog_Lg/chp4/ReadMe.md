# Chp4 Functions and Program Structure

## 4.3 External variables

External variables are defined outside of any function, and thus potentionally available to many functions. Functions are themselves are always external.

***external linkage*** External variables and functions have the property that all references to them by the same name, even for functions compiled separately, are references to the same thing.

## 4.4 Scope Rules

The scope of an external variable or a function lasts from the point at which it is declared to the end of the file being compiled.

## 4.5 Header Files

### declaration of external variable

There must be ***only one definition*** of external variable among all the files that make up the source program, other files may contain ***extern*** declarion to access it.

```c
extern int sp;
extern double val[];
```

### definition of external variable: allocate memory

```c
#define MAXVAL 100
int sp;
double val[MAXVAL]; // also serve as declarations for the rest of file
```

## 4.6 Static Variables

1. External static variable: most widely used, hide data info from other files, but can be accessed by all functions inside the file.
2. Static function: unlike ***external function***, which defined once and can be accessed by all other parts of the program, static function can only be accessed inside the file.
3. Internal static variable: unlike ***automatic variable in a function***, which is born when entering the function and dead after leaving the function, ***static variable in a function*** lives in a permanent storage.

## 4.7 Register Variables

1. Advised compiler that the varible should be placed in registers.
2. Cannot take address of register variables
3. Restricted by machine

## 4.8 Block Structure

## 4.9 Initialization

1. external and static variable:

   In the absence of explicit initialization, the default initial value is 0.
   Initializer must be const-expression.

2. automatic variable inside function:

   In the absence of explicit initialization, the default initial value is undefined.
   Initializer can be any form, const-expression, other variables, value returned by functions...

3. array

   ```c
   int a[5] = {0, 1, 2, 3, 4};
   int a[] = {0, 1, 2, 3, 4}; // same as above
   ```

4. string

   ```c
   char* a = "hello";
   char a[] = "hello";
   char a[] = {'h', 'e', 'l', 'l', 'o', '\0'};
   ```

## 4.10 Recursion
