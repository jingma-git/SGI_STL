#include <iostream>
#include <string>
using namespace std;

// class Transanction
// {
// public:
//     Transanction()
//     {
//         cout << "Transanction" << endl;
//         logTransanction();
//     }

//     virtual void logTransanction() const;
// };

// class BuyTransation : public Transanction
// {
// public:
//     virtual void logTransaction() const
//     {
//         cout << "buy transaction" << endl;
//     }
// };

class Transanction
{
public:
    Transanction() {}

    Transanction(const std::string &translog)
    {
        logTransanction(translog);
    }

    void logTransanction(const string &log) const
    {
        cout << log << endl;
    }
};

class BuyTransanction : public Transanction
{
public:
    BuyTransanction() : Transanction(createLogString())
    {
    }

private:
    static std::string createLogString()
    {
        return "BuyTransanction";
    }
};

class SellTransanction : public Transanction
{
public:
    SellTransanction() : Transanction(createLogString())
    {
    }

private:
    static std::string createLogString()
    {
        return "SellTransanction";
    }
};

int main()
{
    BuyTransanction bt;
    SellTransanction st;
    return 0;
}