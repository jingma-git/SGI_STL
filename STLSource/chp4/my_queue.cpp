#include <iostream>
#include "m_queue.h"
#include "m_list.h"
#include <assert.h>

using namespace std;

template <class QueueT>
void test(QueueT &q)
{
    q.push(1);
    q.push(3);
    q.push(5);
    q.push(7);

    assert(q.front() == 1);
    q.pop();
    assert(q.front() == 3);
    q.pop();
    assert(q.front() == 5);
    q.pop();
    assert(q.front() == 7);
    assert(q.size() == 1);
    q.pop();
    assert(q.size() == 0);
}

int main()
{
    mj::queue<int> q;
    test(q);

    mj::queue<int, mj::list<int>> listQ;
    test(listQ);
    return 0;
}