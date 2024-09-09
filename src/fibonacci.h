#pragma once
#include <vector>


class Fibonacci
{
public:
    Fibonacci(int number);
    void Update();
    void Draw();
    void DrawFibonacciRecursively(int n, int x, int y, int offsetX, int offsetY);

private:
    int number;
};