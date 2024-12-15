#include <vector>
#include "merge_sort.h"
#include "utils.h"
#include <random>
#include <chrono>
#include <thread>

MergeSort :: MergeSort(int size)
{   
    this->Custom_Utils = utils();
    this->size = size;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 100);
    for (int i = 0 ; i<this->size; i++){
        this->random_array.push_back(dis(gen));
    }
    this->isSorted=false;
    close = false;
    
}

void MergeSort :: Draw(){
    //utils Custom_Utils = utils();
    BeginDrawing();
    ClearBackground(RAYWHITE);
    Custom_Utils.Draw2dArray(this->random_array, size);
    utils::TextInfo back_button = {"Back Button", 82, 82, 20};
    bool hovering = Custom_Utils.IsMouseOverText(back_button.text, back_button.x, back_button.y, back_button.fontSize);
    if (hovering) {
                DrawText(back_button.text, back_button.x, back_button.y, back_button.fontSize, BLUE); // Hover color
                DrawLine(back_button.x, back_button.y + back_button.fontSize, back_button.x + MeasureText(back_button.text, back_button.fontSize), back_button.y + back_button.fontSize, BLUE); // Underline
            } else {
                DrawText(back_button.text, back_button.x, back_button.y, back_button.fontSize, BLACK); // Default color
            }
    if (hovering && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {this->close=true;}
    EndDrawing();
    //std::this_thread::sleep_for(std::chrono::milliseconds(0.001));
    
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
            if (close) return;
        }
        k++;
    }


    while (i < n1) {
        x[k] = L[i];
        i++;
        k++;
        this->Draw();
        if (close) return;
    }


    while (j < n2) {
        x[k] = R[j];
        j++;
        k++;
        this->Draw();
        if (close) return;
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
    
    while(!close){
        if (close) {
            return; 
        }
        if (this->isSorted==false){
            this->merge_sort(this->random_array,0,this->size);
        }
        if (this->isSorted==true){
            this->Draw();
        }
        
    }

}