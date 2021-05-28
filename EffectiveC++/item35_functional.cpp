#include <iostream>
#include <functional>
using namespace std;

// alternatives to virtual function
// strategy pattern

class GameCharacter;

int defaultHealthCal(const GameCharacter &c);

class GameCharacter
{
public:
    typedef std::function<int(const GameCharacter)> HealthCalFunc;

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

class GameLevel
{
public:
    float health(const GameCharacter &) const
    {
        return 10.0;
    }
};

int defaultHealthCal(const GameCharacter &c)
{
    return 100;
}

int main()
{
    using namespace std::placeholders;
    EvilBadGuy ebg1;
    cout << ebg1.healthValue() << endl;
    GameLevel game_level;
    EvilBadGuy ebg2(std::bind(&GameLevel::health, game_level, _1)); //ToDO: bind member func
    cout << ebg2.healthValue() << endl;
    return 0;
}