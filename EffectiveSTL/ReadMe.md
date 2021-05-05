# Containers

## Item 1. Choose your containers with care

1. Transactional roll back: node container
2. Iterator, pointer, and reference invalidation: node container
3. Need to be sorted: hash-based container is not suitable
4. Reference counting ? string

## Item 2. Beaware the illusion of container-independent code

1. Associative containers offer logN-time lower_bound, upper_bound, and equal_range member functions, but sequence containers do not.
2. operator[] exists for map not for multimap
3. To make container change easier, write the following code

```cpp
//!!! typedef is your friend
class Widget{...};
typedef vector<Widget, SpecialAllocator<Widget>> WidgetContainer;
typedef WidgetContainer::iterator WIterator;

WidgetContainer vw;
Widget bestWidget;
WIterator it = find(vw.begin(), vw.end(), bestWidget);
```

## Item 3. Make copying cheap and correct for objects in containers

1. Copy in, copy out. The STL way.

## Item 4. Call empty() instead of c.size()==0
## Item 5. Prefer range member functions to their single-element counterparts +++
## Item 6. Be alert for C++'s most vexing parse ?
## Item 7. When using containers of newed pointers, remember to delete the pointers before container is destroyed
## Item 8. Never create containers of auto_ptrs

## Item 9. Choose carefully among erasing options ? +

1. Sequence container: return a new iterator
2. Associative Container: nothing

## Item 10. Be aware of allocator conventions and restrictions +
## Item 11. Understand the legitimate uses of custom allocators
## Item 12. Have realistic expectations about the thread safety of STL containers

# vector and string
## Item 13. Prefer vector and string to dynamically allocated arrays +
## Item 14. Use reserve to avoid unnecessary allocations (OK) ++
## Item 15. Be aware of variations in string implementations
## Item 16. Know how to pass vector and string data to legacy APIs +
## Item 17. Use "the swap trick" to trim excess capacity ?
## Item 18. Avoid using vector<bool> +


# Associative Containers
## Item 19. Understand the difference between equality and equivalence ?
## Item 20. Specify comparison types for associative containers of pointers ?
## Item 21. Always have comparison functions return false for equal values
## Item 22. Avoid in-place key modification in set and multiset
## Item 23. Consider replacing associative containers with sorted vectors +
## Item 24. Choose carefully between map::operator[] and map-insert when efficiency is important
## Item 25. Famlarize yourself with nonstandard hashed containers (OK) +

# Iterators
## Item 26. Prefer iterator to const iterator, reverse iterator, const reverse iterator
## Item 27. Use distance and advance to convert a container's const_iterator to iterator
## Item 28. Understand how to use a reverse_iterator's base iterator
## Item 29. Consider istreambuf_iterators for character-by-character input

# Algorithms
## Item 30. Make sure destination ranges are big enough
## Item 31. Know your sorting options ++

1. Use random access iterator: sort, stable_sort, partial_sort, nth_element

## Item 32. Follow remove-like algorithms by erase if you really want to remove something (OK) +
## Item 33. Be wary of remove-like algorithms on containers of pointers
## Item 34. Note which algorithms expect sorted ranges
    set_union, set_difference, set_intersection, set_sym_difference
## Item 35. Implement simple case-insensitive comparisons via mismatch or lexicographical compare
## Item 36. Understand the proper implementation of copy_if
## Item 37. Use accumulate for_each to summarize ranges

# Functors, Functor Classes, Functions, etc
## Item 38. Design functor classes for pass-by-value ?
## Item 39. Make predicates pure functions ?
## Item 40. Make functor classes adaptable
## Item 41. Understand the reasons for ptr_fun, mem_fun, and mem_fun_ref ?
## Item 42. Make sure less<T> means operator<

# Programming with STL
## Item 43. Prefer algorithm calls to hand-written loops
## Item 44. Prefer member functions to algorithms with the same names (OK)
    set.find() O(logN) whereas std::find O(N)
## Item 45. Distinguish among count, find, binary_search, lower_bound, upper_bound, and equal_range
## Item 46. Consider function objects instead of functions as algorithm parameters
## Item 47. Avoid producing write-only code
## Item 48. Always #include proper headers
## Item 49. Learn to decipher STL-related compiler diagnostics ?
## Item 50. Familarize yourself with STL-related web sites
