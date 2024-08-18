#include <vector>
#include "merge_sort.h"
#include "utils.h"
#include <random>
#include <chrono>
#include <thread>

MergeSort :: MergeSort(int size)
{
    this->size = size;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 100);
    for (int i = 0 ; i<this->size; i++){
        this->random_array.push_back(dis(gen));
    }
    this->isSorted=false;
}

void MergeSort :: Draw(){
    utils Custom_Utils = utils();
    BeginDrawing();
    ClearBackground(RAYWHITE);
    Custom_Utils.Draw2dArray(this->random_array, size);
    EndDrawing();
    std::this_thread::sleep_for(std::chrono::milliseconds(25));

}




void MergeSort :: merge(std::vector<int>& x, int left, 
                     int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<int> L(n1), R(n2);


    for (int i = 0; i < n1; i++)
        L[i] = x[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = x[mid + 1 + j];

    int i = 0, j = 0;
    int k = left;


    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            x[k] = L[i];
            i++;
            this->Draw();
        }
        else {
            x[k] = R[j];
            j++;
            this->Draw();
        }
        k++;
    }


    while (i < n1) {
        x[k] = L[i];
        i++;
        k++;
        this->Draw();
    }


    while (j < n2) {
        x[k] = R[j];
        j++;
        k++;
        this->Draw();
    }
    if ((n1+n2)==this->size){
        isSorted = true;
    }
}


void MergeSort :: merge_sort(std::vector<int>& x, int left, int right)
{
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;
    merge_sort(x, left, mid);
    merge_sort(x, mid + 1, right);
    this->merge(x, left, mid, right);
}


void MergeSort :: Update()
{   
    if (this->isSorted==false){
        this->merge_sort(this->random_array,0,this->size);
    }
    if (this->isSorted==true){
        this->Draw();
    }
    

}