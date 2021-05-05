#include <iterator> // iterator adapters
#include <deque>
#include <algorithm> // copy
#include <iostream>
using namespace std;

ostream_iterator<int> outite(cout, " ");
int ia[] = {0, 1, 2, 3, 4, 5};
deque<int> id(ia, ia + 6);

void test_insert_iterator()
{
    copy(id.begin(), id.end(), outite);
    cout << endl;

    copy(ia + 1, ia + 2, front_inserter(id));
    copy(id.begin(), id.end(), outite);
    cout << endl;

    copy(ia + 3, ia + 4, back_inserter(id));
    copy(id.begin(), id.end(), outite);
    cout << endl;

    deque<int>::iterator ite = find(id.begin(), id.end(), 5);
    copy(ia + 0, ia + 3, inserter(id, ite));
    copy(id.begin(), id.end(), outite);
    cout << endl;
}

void test_reverse_iterator()
{
    copy(id.rbegin(), id.rend(), outite);
    cout << endl;
}

void test_iostream_iterator()
{
    istream_iterator<int> inite(cin), eos; // end-of-stream
    copy(inite, eos, inserter(id, id.begin()));
    copy(id.begin(), id.end(), outite);
}

int main()
{
    test_insert_iterator();
    test_reverse_iterator();
    test_iostream_iterator(); // cat int.dat | ./build/main
    return 0;
}