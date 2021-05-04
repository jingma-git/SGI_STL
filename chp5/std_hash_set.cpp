#include <hash_set>
#include <iostream>
#include <cstring>

using namespace std;

struct eqstr
{
    bool operator()(const char *s1, const char *s2) const
    {
        return strcmp(s1, s2) == 0;
    }
};
typedef __gnu_cxx::hash_set<const char *, hash<const char *>, eqstr> Set;

void lookup(const Set &set, const char *word)
{
    Set::iterator it = set.find(word);
    cout << word << ": " << (it != set.end() ? "Present" : "Not Present") << endl;
}

int main()
{
    Set set;
    set.insert("kiwi");
    set.insert("plum");
    set.insert("apple");
    set.insert("mango");
    set.insert("apricot");
    set.insert("banana");

    lookup(set, "mango");
    lookup(set, "apple");
    lookup(set, "durian");

    __gnu_cxx::hash_set<int> iset;
    iset.insert(59);
    iset.insert(63);
    iset.insert(108);
    iset.insert(2);
    iset.insert(53);
    iset.insert(55);

    // default bucket size is 100, thus the output seems ordered
    cout << "bucket size=" << iset.bucket_count() << endl;
    for (auto it = iset.begin(); it != iset.end(); ++it)
        cout << *it << ' ';
    cout << endl;

    iset.insert(195);
    iset.insert(200);
    iset.insert(199);
    cout << "after insert value exceeds bucket size" << iset.bucket_count() << endl;
    for (auto it = iset.begin(); it != iset.end(); ++it)
        cout << *it << ' ';
    cout << endl;
    return 0;
}