# adapters

1. c means container, it means iterator

## container adapter

1. deque adapters: stack, queue
2. RB-tree adapters: set, multiset, map, multimap
3. Hashtable adapters: hash_set, multi_hashset, hash_map, multi_hashmap

## iterator adapter

1. insert iterator: operator++, operator--, operator*, operator-> are meaningless
   1. front_inserter(c)
   2. back_inserter(c)
   3. inserter(c, it)
2. reverse iterator
3. iostream iterator: how to make our own customized iterator to bind to certain device

## function adapter

container is implemented by 'class template', algorithm is implemented by 'function template',
functor adapter can glue all functors together and make an experssion

1. bind

```cpp
bind1st(const Op& op, const T& x) == op(x, param)
bind2nd(const Op& op, const T& x) == op(param, x)
```

2. negate
3. compose