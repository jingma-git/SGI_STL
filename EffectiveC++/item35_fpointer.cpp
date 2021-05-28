#include <iostream>
using namespace std;

// alternatives to virtual function
// strategy pattern

class GameCharacter;

int defaultHealthCal(const GameCharacter &c);

class GameCharacter
{
public:
    typedef int (*HealthCalFunc)(const GameCharacter &c);

    explicit GameCharacter(HealthCalFunc hcf = defaultHealthCal)
        : health_cal_func(hcf) {}

    int healthValue()
    {
        return health_cal_func(*this);
    }

private:
    HealthCalFunc health_cal_func;
};

class EvilBadGuy : public GameCharacter
{
public:
    explicit EvilBadGuy() {}
    explicit EvilBadGuy(HealthCalFunc hcf) : GameCharacter(hcf) {}
};

int defaultHealthCal(const GameCharacter &c)
{
    return 100;
}

int slowHealthCal(const GameCharacter &c)
{
    return 10;
}

int main()
{
    EvilBadGuy ebg1(defaultHealthCal);
    cout << ebg1.healthValue() << endl;
    EvilBadGuy ebg2(slowHealthCal);
    cout << ebg2.healthValue() << endl;
    return 0;
}