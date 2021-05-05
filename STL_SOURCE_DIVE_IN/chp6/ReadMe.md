## set operation
only suitable for set/multiset that is sorted_range, not suitable for hash_set/hash_multiset because they are not range_sorted

## unique
unique could only remove continous repetitive element, if you wan to find unique element for an unordered sequence, you must sort them first

## sort
set/map are already sorted because underlying RB-tree datastructure <br>
std::sort() must take RandomAccessIterator, thus, vector and deque are suitable whereas list is not suitable <br>
When data amount is large, use Quick Sort. When data amount is smaller than certain threshold, use insertion sort. When recursions are too deep, use heap sort, poping largest element by calling pop_heap().