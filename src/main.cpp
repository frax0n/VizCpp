#include <raylib.h>
#include <vector>
#include <random>
#include <chrono>
#include <thread>
#define RAYGUI_IMPLEMENTATION
#include "include/raygui.h" 
#include "bubble_sort.h"
#include "merge_sort.h"



int main(){
    enum State {
    MENU,
    BUBBLE_SORT,
    MERGE_SORT,
    STOPPED,
    ERROR};

    State currentState = MENU;



    const int screenWidth = 1600;
    const int screenHeight = 900;

    InitWindow(screenWidth,screenHeight,"Raylib Project");
    SetTargetFPS(60);
    
    std::vector<int> rand_array;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 100);
    
    for (int i = 0; i < 40; ++i) {
        rand_array.push_back(dis(gen));
    }

    
    BubbleSort Bubble_Sorting = BubbleSort(40);
    MergeSort Merge_Sorting = MergeSort(40);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Sidebar area for buttons and descriptions
        DrawRectangle(0, 0, 300, screenHeight, LIGHTGRAY);

        if (currentState == MENU) {
            if (GuiButton((Rectangle){ 20, 20, 260, 50 }, "Bubble Sort")) {
                currentState = BUBBLE_SORT;
            }
            if (GuiButton((Rectangle){ 20, 80, 260, 50 }, "Merge Sort")) {
                currentState = MERGE_SORT;
            }

            
            if (currentState == MENU) {
                DrawText("Sorting Algorithms", 20, 150, 20, DARKGRAY);
                DrawText("Bubble Sort: A simple comparison-\nbasedsorting algorithm \nwith O(n^2) complexity.", 20, 200, 16, DARKGRAY);
                DrawText("Merge Sort: A divide-and-conquer\n algorithmwith O(n log n) \ncomplexity.", 20, 280, 16, DARKGRAY);
            }
        }

        // Main area for visualization
        DrawRectangle(300, 0, screenWidth - 300, screenHeight, RAYWHITE);
        switch (currentState) {
            case BUBBLE_SORT:
                Bubble_Sorting.Update();
                break;
            case MERGE_SORT:
                Merge_Sorting.Update();
                break;
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;

}