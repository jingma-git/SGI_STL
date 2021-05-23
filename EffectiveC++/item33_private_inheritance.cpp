#include <iostream>
using namespace std;
// all public and protected members of the base class are accessible as private members of the derived class
// (private members of the base are never accessible unless friended).
// policy design, compile time polymorphism
template <class Transport>
class Service : private Transport
{
public:
    void transmit()
    {
        this->send();
    }
};

class TCP
{
public:
    void send()
    {
        cout << "tcp" << endl;
    }
};

class UDP
{
public:
    void send()
    {
        cout << "udp" << endl;
    }
};

int main()
{
    Service<TCP> s;
    s.transmit();
    // s.send(); // error! private inheritance make all members from base class private
    Service<UDP> s_udp;
    s_udp.transmit();
    return 0;
}