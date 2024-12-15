#pragma once
#include <vector>
#include "utils.h"

class utils;


class MergeSort
{
public:
    MergeSort(int size);
    void merge(std::vector<int>& x,int left,int mid,int right);
    void merge_sort(std::vector<int>& x, int left, int right);
    void Update();
    void Draw();

private:
    utils Custom_Utils;
    std::vector<int> random_array;
    int size;
    bool isSorted;
    bool close;
};