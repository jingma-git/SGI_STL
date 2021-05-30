#include <iostream>
using namespace std;

class CompanyA
{
public:
    void sendClearText()
    {
        cout << "CompanyA::sendClearText" << endl;
    }

    void sendEncryptedText()
    {
        cout << "CompanyA::sendEncryptedText" << endl;
    }
};

class CompanyB
{
public:
    void sendClearText()
    {
        cout << "CompanyB::sendClearText" << endl;
    }

    void sendEncryptedText()
    {
        cout << "CompanyB::sendEncryptedText" << endl;
    }
};