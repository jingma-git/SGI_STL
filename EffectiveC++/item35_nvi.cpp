#include <iostream>
using namespace std;

class GameCharacter
{
public:
    int healthValue()
    {
        // do "before" stuff
        int retVal = doHealthValue();
        // do "after" stuff
        return retVal;
    }

private:
    virtual int doHealthValue() const
    {
        return 100;
    }
};

class EvilBadGuy : public GameCharacter
{
private:
    virtual int doHealthValue() const
    {
        return 10;
    }
};

int main()
{
    GameCharacter gc;
    EvilBadGuy ebg;
    cout << gc.healthValue() << endl;
    cout << ebg.healthValue() << endl;
    return 0;
}