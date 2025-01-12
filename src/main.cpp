#include <raylib.h>
#include <vector>
#include <random>
#include <chrono>
#include <thread>
#include <sstream> 
#include "bubble_sort.h"
#include "merge_sort.h"
#include "utils.h"
#define RAYGUI_IMPLEMENTATION
#include "include/raygui.h" 
#include "bubble_sort.h"
#include "merge_sort.h"
#include <iostream>
#include <math.h>
#include "sinwaves.h"
#include "random_traverse.h"

float RadialFalloff(float x, float y, float centerX, float centerY, float radius)
{
    float distance = sqrt((x - centerX) * (x - centerX) + (y - centerY) * (y - centerY));
    float normalizedDistance = distance / radius;
    if (normalizedDistance > 1.0f) normalizedDistance = 1.0f;
    return (1.0f - normalizedDistance) * (1.0f - normalizedDistance);
}

// int main(){
//     enum State {
//     MENU,
//     BUBBLE_SORT,
//     MERGE_SORT,
//     STOPPED,
//     ERROR};

//     State currentState = MENU;


utils Custom_Utils = utils();

int main(void)
{   bool testMode = true;
    if(testMode == true){
        SetConfigFlags(FLAG_MSAA_4X_HINT);
        
        InitWindow(0, 0, "Test MODE");
        RandomTraverse randomTraverse = RandomTraverse(321,15);
        
        
        while (!WindowShouldClose())    
    {   
        
        BeginDrawing();
        ClearBackground(BLACK);
        DrawCircle(GetScreenWidth()/2,GetScreenHeight()/2,400,LIGHTGRAY);
        randomTraverse.TranverseSeedMod();
        Vector2 circleCenter = { GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f };
        float circleRadius = 400.0f;
        
        EndDrawing();
    }

    }
    else{

    utils Custom_Utils = utils();
    
    InitWindow(0, 0, "Scharnhorst's Phantom");
    const int screenWidth = GetScreenWidth();
    const int screenHeight =  GetScreenHeight();
    std::vector<float> falloffValues(1000 * 1000);
    float falloffRadius = 1000000;
    for (int y = 0; y < 1000; y++) {
    for (int x = 0; x < 1000; x++) {
        falloffValues[y * 1000 + x] = RadialFalloff(x, y, 1000/2, 1000/2, falloffRadius);
    }
    }
    Camera camera = { 0 };
    camera.position = (Vector3){ 7.53425, 6.84932, -11.6438 };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 3.0f, 0.0f };
    camera.fovy = 60.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    Image noiseImage = GenImagePerlinNoise(1000, 1000, 10.0f, 10.0f, 7); 
     // Parameters can be adjusted
    Color *pixels = LoadImageColors(noiseImage);

    for (int y = 0; y < 1000; y++) {
        for (int x = 0; x < 1000; x++) {
            Color pixel = pixels[y * 1000 + x];
        
            float scaleFactor = falloffValues[y * 1000 + x];
            
            
            pixel.r = (int)(pixel.r * scaleFactor);
            pixel.g = (int)(pixel.g * scaleFactor);
            pixel.b = (int)(pixel.b * scaleFactor);
            if(pixel.r < 15 && pixel.g <15  && pixel.b < 15 ){
                pixel.a = 0;

            }
            pixel.a = (int)(pixel.a * scaleFactor);

            pixels[y * 1000 + x] = pixel;
            ImageDrawPixel(&noiseImage, x, y, pixels[y * 1000 + x]); 
        }
    }

    ImageFormat(&noiseImage, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
    Texture2D texture = LoadTextureFromImage(noiseImage); 
    UnloadImageColors(pixels);
    float growthFactor = 0.0f;   
    float growthSpeed = 0.02f; 
    Mesh mesh = GenMeshHeightmap(noiseImage, (Vector3){ 10, 10, 10 }); 
    Model model = LoadModelFromMesh(mesh);                  
    model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
    Vector3 mapPosition = { -5, 0, -5 };           
    UnloadImage(noiseImage);     
    // std::cout<<screenHeight;
    // std::cout<<screenWidth;
    SetTargetFPS(72);              
    // std::cout << "screenHeight: " << screenHeight << std::endl;
    // std::cout << "screenWidth: " << screenWidth << std::endl;


    float camX = 7.53425;
    float camY =  6.84932;
    float camZ = -11.6438 ;
        

    utils::TextInfo texts[] = {
        {"BubbleSort", 82, 757, 20},
        {"MergeSort", 250, 757, 20},
    };

    int numTexts = sizeof(texts) / sizeof(texts[0]);

    // BubbleSort Bubble_Sorting = BubbleSort(300);
    // MergeSort Merge_Sorting = MergeSort(300);

    std::vector<float> originalY(mesh.vertexCount);
    for (int i = 0; i < mesh.vertexCount; i++) {
        originalY[i] = mesh.vertices[i * 3 + 1];  // Store the Y-component of each vertex
    }

    bool needsUpdate = true;

    float startZ =  10.274;
    float endZ = -11.6438 ; 
    SinWaves sineWave = SinWaves(GetScreenWidth(),GetScreenHeight(),0 * (PI / 180.0f),BLACK);
    while (!WindowShouldClose())    
    {

        camera.position = (Vector3){ camX, camY, camZ };
        if (growthFactor < 1.0f) {
            growthFactor += growthSpeed;  
            needsUpdate = true;           
        } else {
            needsUpdate = false;          
        }

       
        if (needsUpdate) {
        for (int i = 0; i < mesh.vertexCount; i++) {
        mesh.vertices[i * 3 + 1] = originalY[i] * growthFactor;  
        camZ = startZ + (endZ - startZ) * growthFactor;
        camera.position = (Vector3){ camX, camY, camZ };
        }}

        
        UpdateMeshBuffer(mesh, 0, mesh.vertices, mesh.vertexCount*3*sizeof(float),0);
        // Drawing
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawRectangle(0, 0, screenWidth, screenHeight / 1.5, LIGHTGRAY);

        GuiSlider((Rectangle){ 100, 100, 600, 20 }, "Camera X", NULL, &camX, -100.0f, 100.0f);
        GuiSlider((Rectangle){ 100, 140, 600, 20 }, "Camera Y", NULL, &camY, 0.0f, 100.0f);
        GuiSlider((Rectangle){ 100, 180, 600, 20 }, "Camera Z", NULL, &camZ, -100.0f, 100.0f);
 
        // sineWave.Update(-100,0,GRAY);
        // sineWave.Update(-100,10,GRAY);
        // sineWave.Update(-100,20,GRAY);
        // sineWave.Update(-100,30,GRAY);
        // sineWave.Update(-100,40,GRAY);
        // sineWave.Update(-100,50,GRAY);

        BeginMode3D(camera);
            
            DrawModel(model, mapPosition, 1.0f, GRAY);
            //DrawGrid(20, 1.0f);
        EndMode3D();
        DrawRectangle(0, screenHeight / 1.5, screenWidth, screenHeight-(screenHeight / 1.5) , WHITE);
        std::ostringstream positionStream;
        positionStream << "Camera Position: X: " << camX << ", Y: " << camY << ", Z: " << camZ;

        for (int i = 0; i < numTexts; i++) {
            bool hovering = Custom_Utils.IsMouseOverText(texts[i].text, texts[i].x, texts[i].y, texts[i].fontSize);

            // Change text color or style based on hover
            if (hovering) {
                DrawText(texts[i].text, texts[i].x, texts[i].y, texts[i].fontSize, BLUE); // Hover color
                DrawLine(texts[i].x, texts[i].y + texts[i].fontSize, texts[i].x + MeasureText(texts[i].text, texts[i].fontSize), texts[i].y + texts[i].fontSize, BLUE); // Underline
            } else {
                DrawText(texts[i].text, texts[i].x, texts[i].y, texts[i].fontSize, BLACK); // Default color
            }


            if (hovering && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                if (i == 0) {
                    BubbleSort Bubble_Sorting = BubbleSort(45);
                    Bubble_Sorting.Update(); 
                } else if (i == 1) {
                    MergeSort Merge_Sorting = MergeSort(70);
                    Merge_Sorting.Update(); 
                }

            }
        }
        DrawText(positionStream.str().c_str(), 40, 50, 25, BLACK);

        
        DrawFPS(10, 10);

        EndDrawing();
    }

    CloseWindow();
    return 0;
    }
}