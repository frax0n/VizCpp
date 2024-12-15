#include <vector>
#include "bubble_sort.h"
#include "utils.h"
#include <random>
#include <chrono>
#include <thread>

BubbleSort :: BubbleSort(int size)
{
    this->size = size;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 500);
    for (int i = 0 ; i<this->size; i++){
        this->random_array.push_back(dis(gen));
    }
    this->IsSorted = false;
}

void BubbleSort :: Draw(){
    utils Custom_Utils = utils();
    BeginDrawing();
    ClearBackground(RAYWHITE);
    Custom_Utils.Draw2dArray(this->random_array, size);
    EndDrawing();
    std::this_thread::sleep_for(std::chrono::milliseconds(1));

}


void BubbleSort :: Update()
{   
    int temp = 0;
    if (IsSorted == false){
        for(int i = 0; i<size-1;i++){
            for(int j=0;j<size-1-i;j++){
                if(this->random_array[j]>this->random_array[j+1]){
                    temp=this->random_array[j+1];
                    this->random_array[j+1]=this->random_array[j];
                    this->random_array[j]=temp;
                    this->Draw();

                    // Pause to make the sorting process visible
                    
                }
            }
            
        }
        IsSorted = true;
    }
    if (IsSorted == true){
        this->Draw();
    }



}
