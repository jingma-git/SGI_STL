class GamePlayer
{
private:
    // enum hack: for compilers that do not accept in-class static const
    enum
    {
        NumTurns = 5
    };
    // static const int NumTurns = 5;
    static const double MaxScores; // in-class intialization is allowed only for integral types and only for constants
    int scores[NumTurns];
};
const double GamePlayer::MaxScores = 100.0;

int main()
{
    return 0;
}