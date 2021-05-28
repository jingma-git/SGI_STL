#include <iostream>
using namespace std;

class B{
public:
// virtual ~B(){
//     cout << "~B" << endl;
// }

~B(){
    cout << "~B" << endl;
}
};

class D:public B{
public:
// virtual ~D(){
//     cout << "~D" << endl;
// }

 ~D(){
    cout << "~D" << endl;
}
};

class Base{
public:
virtual ~Base(){
    cout << "~Base" << endl;
}
};

class Derived: public Base{
public:
virtual ~Derived(){
    cout << "~Derived" << endl;
}
};

int main(){
    // D d; // output: ~D, ~B

    // B* ptr_d = new D;
    // delete ptr_d; 
    // // output ~B if use non-virtual deconstructor, because non-virtual ~B and ~D are static
    // // see: item36

    Derived* ptr_deriv1 = new Derived;
    delete ptr_deriv1;

        Base* ptr_deriv2 = new Derived;
    delete ptr_deriv2;
    return 0;
}