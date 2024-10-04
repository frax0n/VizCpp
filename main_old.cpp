#include <raylib.h>
#include <vector>
#include <random>
#include <chrono>
#include <thread>
#define RAYGUI_IMPLEMENTATION
#include "include/raygui.h" 
#include "bubble_sort.h"
#include "merge_sort.h"



// int main(){
//     enum State {
//     MENU,
//     BUBBLE_SORT,
//     MERGE_SORT,
//     STOPPED,
//     ERROR};

//     State currentState = MENU;



//     const int screenWidth = 1600;
//     const int screenHeight = 900;

//     InitWindow(screenWidth,screenHeight,"Raylib Project");
//     SetTargetFPS(60);
    
//     std::vector<int> rand_array;
//     std::random_device rd;
//     std::mt19937 gen(rd());
//     std::uniform_int_distribution<> dis(1, 100);
    
//     for (int i = 0; i < 40; ++i) {
//         rand_array.push_back(dis(gen));
//     }

    
//     BubbleSort Bubble_Sorting = BubbleSort(40);
//     MergeSort Merge_Sorting = MergeSort(40);

//     while (!WindowShouldClose()) {
//         BeginDrawing();
//         ClearBackground(RAYWHITE);

//         // Sidebar area for buttons and descriptions
//         DrawRectangle(0, 0, 300, screenHeight, LIGHTGRAY);

//         if (currentState == MENU) {
//             if (GuiButton((Rectangle){ 20, 20, 260, 50 }, "Bubble Sort")) {
//                 currentState = BUBBLE_SORT;
//             }
//             if (GuiButton((Rectangle){ 20, 80, 260, 50 }, "Merge Sort")) {
//                 currentState = MERGE_SORT;
//             }

            
//             if (currentState == MENU) {
//                 DrawText("Sorting Algorithms", 20, 150, 20, DARKGRAY);
//                 DrawText("Bubble Sort: A simple comparison-\nbasedsorting algorithm \nwith O(n^2) complexity.", 20, 200, 16, DARKGRAY);
//                 DrawText("Merge Sort: A divide-and-conquer\n algorithmwith O(n log n) \ncomplexity.", 20, 280, 16, DARKGRAY);
//             }
//         }

//         // Main area for visualization
//         DrawRectangle(300, 0, screenWidth - 300, screenHeight, RAYWHITE);
//         switch (currentState) {
//             case BUBBLE_SORT:
//                 Bubble_Sorting.Update();
//                 break;
//             case MERGE_SORT:
//                 Merge_Sorting.Update();
//                 break;
//         }

//         EndDrawing();
//     }

//     CloseWindow();
//     return 0;

// }

// int main2(void)
// {
//     // Initialization
//     //--------------------------------------------------------------------------------------
//     const int screenWidth = 800;
//     const int screenHeight = 450;

//     InitWindow(screenWidth, screenHeight, "raylib [models] example - heightmap loading and drawing");

//     // Define our custom camera to look into our 3d world
//     Camera camera = { 0 };
//     camera.position = (Vector3){ 18.0f, 21.0f, 18.0f };     // Camera position
//     camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };          // Camera looking at point
//     camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };              // Camera up vector (rotation towards target)
//     camera.fovy = 45.0f;                                    // Camera field-of-view Y
//     camera.projection = CAMERA_PERSPECTIVE;                 // Camera projection type

//     Image image = LoadImage("heightmap.png");     // Load heightmap image (RAM)
//     Texture2D texture = LoadTextureFromImage(image);        // Convert image to texture (VRAM)

//     Mesh mesh = GenMeshHeightmap(image, (Vector3){ 16, 8, 16 }); // Generate heightmap mesh (RAM and VRAM)
//     Model model = LoadModelFromMesh(mesh);                  // Load model from generated mesh

//     model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture; // Set map diffuse texture
//     Vector3 mapPosition = { -8.0f, 0.0f, -8.0f };           // Define model position

//     UnloadImage(image);             // Unload heightmap image from RAM, already uploaded to VRAM

//     SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
//     //--------------------------------------------------------------------------------------

//     // Main game loop
//     while (!WindowShouldClose())    // Detect window close button or ESC key
//     {
//         // Update
//         //----------------------------------------------------------------------------------
//         UpdateCamera(&camera, CAMERA_ORBITAL);
//         //----------------------------------------------------------------------------------

//         // Draw
//         //----------------------------------------------------------------------------------
//         BeginDrawing();

//             ClearBackground(RAYWHITE);

//             BeginMode3D(camera);

//                 DrawModel(model, mapPosition, 1.0f, GRAY);

//                 DrawGrid(20, 1.0f);

//             EndMode3D();

//             DrawTexture(texture, screenWidth - texture.width - 20, 20, WHITE);
//             DrawRectangleLines(screenWidth - texture.width - 20, 20, texture.width, texture.height, GREEN);

//             DrawFPS(10, 10);

//         EndDrawing();
//         //----------------------------------------------------------------------------------
//     }

//     // De-Initialization
//     //--------------------------------------------------------------------------------------
//     // UnloadTexture(texture);     // Unload texture
//     // UnloadModel(model);         // Unload model

//     CloseWindow();              // Close window and OpenGL context
//     //--------------------------------------------------------------------------------------

//     return 0;
// }