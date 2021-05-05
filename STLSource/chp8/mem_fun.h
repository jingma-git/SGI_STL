#pragma once

template <class Arg, class Result>
struct unary_function
{
    typedef Arg argument_type;
    typedef Result result_type;
};

template <class Arg1, class Arg2, class Result>
struct binary_function
{
    typedef Arg1 first_argument_type;
    typedef Arg2 second_argument_type;
    typedef Result result_type;
};

// no argument, call by pointer, non-constant member function
template <class S, class T>
class mem_fun_t : public unary_function<T *, S>
{
public:
    explicit mem_fun_t(S (T::*pf)()) : f(pf) {}
    S operator()(T *p) const { return (p->*f)(); }

private:
    S(T::*f) // Pointer to member function
    ();
};

// no argument, call by pointer, constant member function
template <class S, class T>
class const_mem_fun_t : public unary_function<const T *, S>
{
public:
    explicit const_mem_fun_t(S (T::*pf)() const) : f(pf) {}
    S operator()(const T *p) const { return (p->*f)(); }

private:
    S(T::*f) // Pointer to member function
    () const;
};

// no argument, call by reference, non-constant member function
template <class S, class T>
class mem_fun_ref_t : public unary_function<T, S>
{
public:
    explicit mem_fun_ref_t(S (T::*pf)()) : f(pf) {}
    S operator()(T &r) const { return (r.*f)(); }

private:
    S(T::*f) // Pointer to member function
    ();
};

// no argument, call by reference, constant member function
template <class S, class T>
class const_mem_fun_ref_t : public unary_function<T, S>
{
public:
    explicit const_mem_fun_ref_t(S (T::*pf)() const) : f(pf) {}
    S operator()(const T &r) const { return (r.*f)(); }

private:
    S(T::*f) // Pointer to member function
    () const;
};

// one argument, call by pointer, non-constant member function
template <class S, class T, class A>
class mem_fun1_t : public binary_function<T *, A, S>
{
public:
    explicit mem_fun1_t(S (T::*pf)(A)) : f(pf) {}
    S operator()(T *p, A x) const { return (p->*f)(x); }

private:
    S(T::*f) // Pointer to member function
    (A);
};

// one argument, call by pointer, constant member function
template <class S, class T, class A>
class const_mem_fun1_t : public binary_function<const T *, A, S>
{
public:
    explicit const_mem_fun1_t(S (T::*pf)(A) const) : f(pf) {}
    S operator()(const T *p, A x) const { return (p->*f)(x); }

private:
    S(T::*f) // Pointer to member function
    (A) const;
};

// one argument, call by reference, non-constant member function
template <class S, class T, class A>
class mem_fun1_ref_t : public binary_function<T, A, S>
{
public:
    explicit mem_fun1_ref_t(S (T::*pf)(A)) : f(pf) {}
    S operator()(T &r, A x) const { return (r.*f)(x); }

private:
    S(T::*f) // Pointer to member function
    (A);
};

// one argument, call by reference, constant member function
template <class S, class T, class A>
class const_mem_fun1_ref_t : public binary_function<T, A, S>
{
public:
    explicit const_mem_fun1_ref_t(S (T::*pf)(A) const) : f(pf) {}
    S operator()(const T &r, A x) const { return (r.*f)(x); }

private:
    S(T::*f) // Pointer to member function
    (A) const;
};