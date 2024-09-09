#include "utils.h"
#include <vector>
#include "../include/raylib.h" 

void utils::Draw2dArray(std::vector<int> &array,int size){
    int rectWidth = 30;
    int rectHeigthMultiplier = 4;

    for (int i = 0; i<size; i++){
        int x = 100 + i * (rectWidth + 5);
        int y = 500 - array[i] * rectHeigthMultiplier;

        DrawRectangle(x,y,rectWidth,array[i]*rectHeigthMultiplier,PURPLE);
        
    }

}