#include <iostream>
using namespace std;

class CompanyA
{
public:
    void sendClearText(const std::string &msg)
    {
        cout << "CompanyA::sendClearText" << endl;
    }

    void sendEncryptedText(const std::string &msg)
    {
        cout << "CompanyA::sendEncryptedText" << endl;
    }
};

class CompanyB
{
public:
    void sendClearText(const std::string &msg)
    {
        cout << "CompanyB::sendClearText" << endl;
    }

    void sendEncryptedText(const std::string &msg)
    {
        cout << "CompanyB::sendEncryptedText" << endl;
    }
};

class CompanyC
{
public:
    void sendEncryptedText(const std::string &msg)
    {
        cout << "CompanyC::sendEncryptedText" << endl;
    }
};

class MsgInfo
{
};

template <typename Company>
class MsgSender
{
public:
    void sendClear(const MsgInfo &info)
    {
        std::string msg;
        // create msg from info

        Company c;
        c.sendClearText(msg);
    }

    void sendSecret(const MsgInfo &info)
    {
        std::string msg;
        // create msg from info

        Company c;
        c.sendEncryptedText(msg);
    }
};

template <>               // neighther a template nor a standalone class
class MsgSender<CompanyC> //full/explicit template specialization
{
public:
    void sendSecret(const MsgInfo &info)
    {
        std::string msg;
        // create msg from info

        CompanyC c;
        c.sendEncryptedText(msg);
    }
};

template <typename Company>
class LoggingMsgSender : public MsgSender<Company>
{
public:
    // using MsgSender<Company>::sendClear; // solution 2
    void sendClearMsg(const MsgInfo &info)
    {
        // write 'before sending' info to log

        // // error: there are no arguments to ‘sendClear’ that depend on a template parameter
        // // when it comes to template_inheritance, compiler assume it desn't know any names from template_base_class
        // sendClear(info);

        // solution 1
        this->sendClear(info);

        // // solution 2: search in Base_class's namespace
        // sendClear(info);

        // // solution 3: least desirable
        // // if the function being called is virtual,
        // // explicit qualification turns off the virtual binding behavior
        // MsgSender<Company>::sendClear(info);

        // write 'after sending' info to log
    }
};

int main()
{
    MsgInfo infoA;
    MsgSender<CompanyA> msgSenderA;
    msgSenderA.sendClear(infoA);

    MsgInfo infoB;
    MsgSender<CompanyB> msgSenderB;
    msgSenderB.sendClear(infoB);

    // MsgInfo infoC;
    // MsgSender<CompanyC> msgSenderC;
    // msgSenderC.sendClear(); // doesn't compile since CompanyC doesn't have sendClearText() func
    return 0;
}