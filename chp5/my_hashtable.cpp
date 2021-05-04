#include <iostream>
#include "m_hashtable.h"

using namespace std;

int main()
{
    typedef mj::hashtable<int, int, mj::hash<int>, mj::identity<int>, mj::equal_to<int>> HashTable;
    typedef typename HashTable::iterator iterator;
    HashTable iht(50, mj::hash<int>(), mj::equal_to<int>());

    // cout << iht.size() << endl;
    cout << iht.bucket_count() << endl;
    cout << iht.max_bucket_count() << endl;

    iht.insert_unique(59);
    iht.insert_unique(63);
    iht.insert_unique(108);
    iht.insert_unique(2);
    iht.insert_unique(53);
    iht.insert_unique(55);
    cout << "tablesize=" << iht.size() << endl;

    iterator it = iht.begin();
    cout << "nodes:";
    for (; it != iht.end(); ++it)
        cout << *it << " ";
    cout << endl;

    for (int i = 0; i < iht.bucket_count(); ++i)
    {
        // bucket[2] has 3 elems. 108, 2, 55
        int n = iht.elems_in_bucket(i);
        if (n != 0)
            cout << "bucket[" << i << "] has " << n << " elems." << endl;
    }

    cout << "Test rehash..." << endl;
    for (int i = 0; i <= 47; ++i)
        iht.insert_equal(i);
    cout << "size=" << iht.size() << endl;
    cout << "bucket=" << iht.bucket_count() << endl;

    for (int i = 0; i < iht.bucket_count(); ++i)
    {
        // bucket[2] has 2 elems. 2, 2
        // bucket[11] has 2 elems. 11, 108
        int n = iht.elems_in_bucket(i);
        if (n != 0)
            cout << "bucket[" << i << "] has " << n << " elems." << endl;
    }
    cout << "nodes:";
    for (it = iht.begin(); it != iht.end(); ++it)
        cout << *it << " ";
    cout << endl;

    cout << *(iht.find(2)) << endl;
    cout << iht.count(2) << endl;
    return 0;
}