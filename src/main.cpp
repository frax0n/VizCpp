#include "raylib.h" 
#include <vector>
#include <random>
#include <chrono>
#include <thread>
#define RAYGUI_IMPLEMENTATION
#include "raygui.h" 
#include "bubble_sort.h"
#include "merge_sort.h"
#include "fibonacci.h"
#include <stdio.h>
#include <unistd.h>


int main(){
    enum State {
    MENU,
    BUBBLE_SORT,
    MERGE_SORT,
    FIBONACCI,
    STOPPED,
    ERROR};

    State currentState = MENU;
    int x = (int)(GetMonitorWidth(0) * 0.7);
    int y = (int)(GetMonitorHeight(0)* 0.7);
    const int screenWidth = x;
    const int screenHeight = y;

    InitWindow(screenWidth,screenHeight,"Algorithm Visualization");
    SetTargetFPS(60);

    fprintf(stderr, "Printing in console.\n");
    fprintf(stderr, "screenWidth ,screenHeight:%i:%i,%i:%i\n",GetMonitorWidth(0),x,GetMonitorHeight(0),y);

    BubbleSort Bubble_Sorting =  BubbleSort(35);
    MergeSort Merge_Sorting =  MergeSort(35);
    Fibonacci Fibonacci_viz = Fibonacci(5);
    while (!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(WHITE);
        if (currentState == MENU){
            if(GuiButton((Rectangle){ 24, 24, 120, 30 },"Bubble Sort") == true){
            currentState = BUBBLE_SORT;
        }
            if(GuiButton((Rectangle){ 24, 48, 120, 30 },"Merge Sort") == true){
                currentState = MERGE_SORT;
        }
            if(GuiButton((Rectangle){ 24, 72, 120, 30 },"Fibonacci") == true){
                currentState = FIBONACCI;
        }
        }
        switch(currentState){
            case BUBBLE_SORT:
                Bubble_Sorting.Update();
                break;
            case MERGE_SORT:
                Merge_Sorting.Update();
                break;
            case FIBONACCI:
                Fibonacci_viz.Draw();
                break;
        }
        EndDrawing(); 

    }
    CloseWindow(); 

    return 0; 

}