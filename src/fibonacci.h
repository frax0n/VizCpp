#pragma once
#include <vector>


class Fibonacci
{
public:
    Fibonacci(int size);
    void Update();
    void Draw();
private:
    std::vector<int> random_array;
    int size;
};