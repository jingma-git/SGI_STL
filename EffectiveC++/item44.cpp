#include <iostream>
using namespace std;

template <typename T>
class SquareMatrixBase // size-independent base class for SquareMatrix
{
protected:
    SquareMatrixBase(int n, T *pMem) : size(n), pData(pMem) {}

    void setDataPtr(T *ptr) { pData = ptr; }

    // don't use implicit inline here
    // because code bloat occurs instantiating SquareMatrix<T, n>
    void invert();

private:
    int size;
    T *pData;
};

template <typename T, int n>
class SquareMatrix : private SquareMatrixBase<T>
{
public:
    SquareMatrix() : SquareMatrixBase<T>(n, data) {}

    // simple inline class to non-inline base class versions
    // that are shared with all other matrices holding the same type of data
    // regardless of their size
    void invert()
    {
        SquareMatrixBase<T>::invert();
    }

private:
    T data[n * n];
};

template <typename T>
class SquareMatrixX : private SquareMatrixBase<T>
{
public:
    SquareMatrixX(int n)
        : SquareMatrixBase<T>(n, 0),
          data(new T[n * n])
    {
        // when it comes to template_inheritance, compiler assumes it doesn't know any names
        // from template_base_class
        // becuase some template may have the name
        // while other doesn't have, eg. full expecilization of MsgSender<CompanyC>
        this->setDataPtr(data); // see item43: how to access names from template_base_class
    }

    ~SquareMatrixX()
    {
        delete[] data;
    }
    // simple inline class to non-inline base class versions
    // that are shared with all other matrices holding the same type of data
    // regardless of their size
    void invert()
    {
        SquareMatrixBase<T>::invert();
    }

private:
    T *data; // or use boost::scoped_array<T> to manage new T[]
};

int main()
{
    SquareMatrix<int, 5> m1;
    m1.invert();

    SquareMatrix<int, 3> m2;
    m2.invert();

    SquareMatrix<double, 3> m3;
    m3.invert();

    SquareMatrixX<int> m(10);
    m.invert();
    return 0;
}

template <typename T>
void SquareMatrixBase<T>::invert()
{
    cout << "SquareMatrixBase<T>::invert() " << size << endl;
}