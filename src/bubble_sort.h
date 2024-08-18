#pragma once
#include <vector>


class BubbleSort
{
public:
    BubbleSort(int size);
    void Update();
    void Draw();
    bool IsSorted;

private:
    std::vector<int> random_array;
    int size;
};