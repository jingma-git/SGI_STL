#include <iostream>
#include <unordered_set>
#include <string>
using namespace std;

struct Person
{
    string name;
    int age;
    Person() {}
    Person(const string &name_, int age_) : name(name_), age(age_) {}

    bool operator==(const Person &p) const
    {
        return name == p.name && age == p.age;
    }
};

struct HashFunction
{
    size_t operator()(const Person &p) const
    {
        size_t xHash = std::hash<std::string>()(p.name);
        size_t yHash = std::hash<int>()(p.age) << 1;
        return xHash ^ yHash;
    }
};

void test_custom_class()
{
    Person p1("Ted", 26);
    unordered_set<Person, HashFunction> pset;
    pset.insert(Person("Ted", 26));
    pset.insert(Person("Robin", 24));
    for (auto &p : pset)
    {
        cout << p.name << ", " << p.age << endl;
    }
}

#include <cstring>

struct eqstr
{
    bool operator()(const char *s1, const char *s2) const
    {
        return strcmp(s1, s2) == 0;
    }
};
typedef unordered_set<const char *, hash<const char *>, eqstr> Set;

void lookup(const Set &set, const char *word)
{
    auto it = set.find(word);
    cout << word << ": " << (it != set.end() ? "Present" : "Not Present") << endl;
}

void test_primary()
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

    unordered_set<int> iset;
    iset.reserve(193);
    iset.insert(59);
    iset.insert(63);
    iset.insert(108);
    iset.insert(2);
    iset.insert(53);
    iset.insert(55);

    // compared with hash_set, the output is not ordered
    cout << "bucket size=" << iset.bucket_count() << endl;
    for (auto it = iset.begin(); it != iset.end(); ++it)
        cout << *it << ' ';
    cout << endl;

    iset.insert(195);
    iset.insert(200);
    iset.insert(199);
    cout << "after insert value exceeds bucket size " << iset.bucket_count() << endl;
    for (auto it = iset.begin(); it != iset.end(); ++it)
        cout << *it << ' ';
    cout << endl;
}

int main()
{
    // test_custom_class();
    test_primary();
    return 0;
}