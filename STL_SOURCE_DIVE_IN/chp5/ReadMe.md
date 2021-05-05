## set
adapter for RB-tree<br>
insert_unique, same elements are not allowed <br>
all iterators are still valid after insert/erase <br>
user cannot modify set's value since it is also used as key

```cpp
typedef rb_tree<key_type, value_type, identity<value_type>, key_compare, Alloc> rep_type;
typedef typename rep_type::const_iterator iterator;
```

## multiset
adapter for RB-tree<br>
insert_equal, same elements are allowed<br>

## map
adapter for RB-tree<br>
use container's find() to search instead of std::find

## hashtable
seperate chainning: use hash(key) % n decides which bucket the element lies in, use singly-linked-list if collision detected
### hash_set && hash_map
adapter for hashtable
## set vs hash_set
set: ordered by RB-tree <br>
hash_set: not ordered