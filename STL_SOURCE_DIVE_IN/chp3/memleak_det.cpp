// https://stackoverflow.com/questions/6261201/how-to-find-memory-leak-in-a-c-code-project
// g++ -fsanitize=address -ggdb3 -o main memleak_det.cpp
// https://stackoverflow.com/questions/50897079/enabling-addresssanitizer-with-cmake
int main()
{
    int *p1 = new int;
    char *p2 = new char[10];
    return 0;
}