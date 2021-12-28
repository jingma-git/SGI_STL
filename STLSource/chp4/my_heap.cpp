#include <iostream>
#include "m_vector.h"
#include "m_heap.h"
#include "m_algo.h"
#include <algorithm>
#include <assert.h>

using namespace std;

void test1()
{
    int ia[5] = {68, 65, 50, 21, 31};
    mj::vector<int> ivec(ia, ia + 5);
    pop_heap(ivec.begin(), ivec.end());
    for (int i = 0; i < 5; ++i)
    {
        cout << ivec[i] << " ";
    }
    cout << endl;
}

void test2()
{
    for (int iter = 0; iter < 10; ++iter)
    {
        int num_eles = rand() % 1000000 + 10;
        int *arr1 = new int[num_eles];
        int *arr2 = new int[num_eles];
        for (int i = 0; i < num_eles; ++i)
        {
            arr1[i] = rand() % 10;
            arr2[i] = arr1[i];
        }
        // std::cout << iter << " num_eles: " << num_eles << std::endl;

        std::pop_heap(arr1, arr1 + num_eles);
        mj::pop_heap(arr2, arr2 + num_eles);

        for (int i = 0; i < num_eles; ++i)
        {
            assert(arr1[i] == arr2[i]);
        }

        delete[] arr1;
        delete[] arr2;
    }
}

int main()
{
    // pop out the max_element, and percolate down the end_element
    // test1();
    test2();

    return 0;
}