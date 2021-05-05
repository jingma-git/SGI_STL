# functors

## Unary functor

```cpp
template <class  Arg, class Result>
struct unary_function{
    typedef Arg argument_type;
    typedef Result result_type;
};

// functor
template <class _Tp>
struct negate : public unary_function<_Tp,_Tp> 
{
  _Tp operator()(const _Tp& __x) const { return -__x; }
};

// adapters
template <class _Predicate>
class unary_negate
  : public unary_function<typename _Predicate::argument_type, bool> {
protected:
  _Predicate _M_pred;
public:
  explicit unary_negate(const _Predicate& __x) : _M_pred(__x) {}
  bool operator()(const typename _Predicate::argument_type& __x) const {
    return !_M_pred(__x);
  }
};
```

## Binary functor

```cpp
template <class Arg1, class Arg2, class Result>
struct binary_function{
    typedef Arg1 first_argument_type;
    typedef Arg2 second_argument_type;
    typedef Result result_type;
};

// functor
template <class T>
struct less: public binary_function<T, T, bool>{
    bool operator()(const T& v1, const T& v2){
        return v1 < v2;
    }
};

// adapters
template <class Operation>
class binder2nd
    : public unary_function<typename Operation::first_argument_type, 
                            typename Operation::result_type>
{
protected:
    Operation op;
    typename Operation::second_argument_type value;
public:
    binder2nd(const Operation& op_, const typename Operation::second_argument_type y):op(op_), value(y){}

    typename Operation::result_type operator()(typename Operation::first_argument_type& x){
        return op(x, value);
    }
}
```