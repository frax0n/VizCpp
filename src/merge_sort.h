#pragma once
#include <vector>

class MergeSort
{
public:
    MergeSort(int size);
    void merge(std::vector<int>& x,int left,int mid,int right);
    void merge_sort(std::vector<int>& x, int left, int right);
    void Update();
    void Draw();

private:
    std::vector<int> random_array;
    int size;
    bool isSorted;
};