#include <algorithm>
#include <numeric>
#include <vector>
#include <functional>
#include <iostream>
#include <iterator>
using namespace std;

template <class T>
struct display
{
    void operator()(const T &val)
    {
        cout << val << " ";
    }
};

int main()
{
    int ia[5] = {1, 2, 3, 4, 5};
    vector<int> iv(ia, ia + 5);
    cout << accumulate(iv.begin(), iv.end(), 0) << endl;
    cout << accumulate(iv.begin(), iv.end(), 0, minus<int>()) << endl;
    cout << inner_product(iv.begin(), iv.end(), iv.begin(), 10) << endl;
    cout << inner_product(iv.begin(), iv.end(), iv.begin(), 10, minus<int>(), plus<int>()) << endl;

    ostream_iterator<int> oite(cout, " ");
    partial_sum(iv.begin(), iv.end(), oite);
    cout << endl;
    vector<int> iv1(iv.size());
    partial_sum(iv.begin(), iv.end(), iv1.begin());
    for_each(iv1.begin(), iv1.end(), display<int>());
    cout << endl;

    adjacent_difference(iv.begin(), iv.end(), oite); // out[n] = in[n] - in[n-1]
    cout << endl;
    adjacent_difference(iv.begin(), iv.end(), oite, plus<int>()); // out[n] = in[n] op in[n-1]
    cout << endl;

    int n = 3;
    iota(iv.begin(), iv.end(), n);
    for_each(iv.begin(), iv.end(), display<int>());
    cout << endl;
    return 0;
}