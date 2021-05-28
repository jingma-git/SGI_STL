#include <iostream>
using namespace std;

class GameCharacter;

class HealthCalFunc
{
public:
    virtual int calc(const GameCharacter &gc) const
    {
        return 100;
    }
};

class SlowHealthCalFunc : public HealthCalFunc
{
public:
    virtual int calc(const GameCharacter &gc) const
    {
        return 10;
    }
};

class GameCharacter
{
public:
    explicit GameCharacter(HealthCalFunc *hcf)
        : health_cal_func(hcf) {}

    int healthValue()
    {
        return health_cal_func->calc(*this);
    }

private:
    HealthCalFunc *health_cal_func;
};

class EvilBadGuy : public GameCharacter
{
public:
    explicit EvilBadGuy(HealthCalFunc *hcf) : GameCharacter(hcf) {}
};

int main()
{
    HealthCalFunc defaultHealthCal;
    EvilBadGuy ebg1(&defaultHealthCal);
    cout << ebg1.healthValue() << endl;
    SlowHealthCalFunc slowHealthCal;
    EvilBadGuy ebg2(&slowHealthCal);
    cout << ebg2.healthValue() << endl;
    return 0;
}