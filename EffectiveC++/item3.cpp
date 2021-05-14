#include <vector>
#include <cstring>
#include <iostream>
using namespace std;

class Rational
{
public:
    Rational(int val_) : val(val_) {}
    friend const Rational operator*(const Rational &a, const Rational &b)
    {
        return a.val * b.val;
    }

private:
    int val;
};

class TextBlock // API for C-style string
{
public:
    TextBlock(const char *text_)
    {
        text = (char *)malloc(strlen(text_) * sizeof(char));
        strcpy(text, text_);
    }

    ~TextBlock() { free(text); }

    // Compiler will not complain, but not Bitwise Constness
    // Client will find way to change data member
    // eg.
    // const TextBlock ctb("hello");
    // ctb[0] = 'j';
    /*const*/ // uncomment this to prevent  ctb[0] = 'j'
    char &operator[](int position) const
    {
        return text[position];
    }

    // Logical constness
    // May change some data members that users not needed to know
    // eg. text_len, is_len_valid
    std::size_t length() const
    {
        text_len = is_len_valid ? strlen(text) : MAX_LEN;
        if (text_len >= MAX_LEN)
            is_len_valid = false;
        return text_len;
    }

    friend std::ostream &operator<<(std::ostream &out, const TextBlock &tb)
    {
        out << tb.text;
        return out;
    }

private:
    static int MAX_LEN;
    char *text;
    mutable size_t text_len;   // mutable: can be modified in any condition
    mutable bool is_len_valid; // mutable: even in constant member function
};
int TextBlock::MAX_LEN = 100;

class TextBlockV1
{
public:
    TextBlockV1(std::string text_) : text(text_) {}

    // const mem_fun
    const char &operator[](int pos) const
    {
        // do bounds checking
        // log access data
        // verify data integrity
        cout << "const mem_fun" << endl;
        return text[pos];
    }

    // char &operator[](int pos)
    // {
    //     // do bounds checking
    //     // log access data
    //     // verify data integrity
    //     return text[pos];
    // }
    char &operator[](int pos)
    {
        cout << "non_const mem_fun" << endl;
        return const_cast<char &>( // cast away constness of return-type for const mem_fun
            static_cast<const TextBlockV1 &>(*this)[pos]
            // cast *this to const and call const mem_fun,
            // also avoiding end-less recursion if invoking on non-constant member
        );
    }

private:
    std::string text;
};

int main()
{
    {
        char greeting[] = "hello";
        char *p0 = greeting;             // non-constant pointer, non-constant data
        const char *p1 = greeting;       // non-constant pointer, const data
        char *const p2 = greeting;       // constant pointer, non-constant data
        const char *const p3 = greeting; // constant pointer, constant data

        // STL iterator acts like raw_pointer
        int a[] = {0, 1, 2};
        std::vector<int> vec(a, a + 3);
        // the iterator/pointer itself cannot be changed
        // but the content it points to can be modified
        const std::vector<int>::iterator iter = vec.begin(); // T* const;
        *iter = 10;
        // ++iter; // error!!! iter is constant

        // the iterator can be changed, but the content it points cannot be changed
        std::vector<int>::const_iterator citer = vec.begin(); // const T*;
        ++citer;
        // *citer = 10; // error!!! *cIter is const
    }

    {
        Rational a(10), b(5), c(50);
        // if (a *b = c) // error!!! not compile. prevent programmer from writing == (comparison) to = (assignment)
        //     ;
    }

    {
        const TextBlock ctb("hello"); // data member should not be modified
        cout << ctb << endl;
        ctb[0] = 'j';
        cout << ctb << endl;
        // Output:
        // hello
        // jello

        cout << "len=" << ctb.length() << endl;
    }

    {
        TextBlockV1 tb("world");
        cout << tb[0] << endl;
        // Output:
        // non_const mem_fun
        // const mem_fun
        // w
    }
    return 0;
}