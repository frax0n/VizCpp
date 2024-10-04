#include <iostream>
#include <raylib.h>
#include <vector>
#include <random>
#include <chrono>
#include <thread>
#include <sstream> 
#include "bubble_sort.h"
#include "merge_sort.h"
#define RAYGUI_IMPLEMENTATION
#include "include/raygui.h" 



float RadialFalloff(float x, float y, float centerX, float centerY, float radius)
{
    float distance = sqrt((x - centerX) * (x - centerX) + (y - centerY) * (y - centerY));
    float normalizedDistance = distance / radius;
    if (normalizedDistance > 1.0f) normalizedDistance = 1.0f;
    return (1.0f - normalizedDistance) * (1.0f - normalizedDistance);
}


bool IsMouseOverText(const char* text, int posX, int posY, int fontSize) {
    Vector2 textSize = MeasureTextEx(GetFontDefault(), text, fontSize, 1);
    Vector2 mousePosition = GetMousePosition();

    return (mousePosition.x >= posX && mousePosition.x <= posX + textSize.x &&
            mousePosition.y >= posY && mousePosition.y <= posY + textSize.y);
}

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    

    InitWindow(0, 0, "raylib [models] example - heightmap loading and drawing");
    const int screenWidth = GetScreenWidth();
    const int screenHeight =  GetScreenHeight();
    Camera camera = { 0 };
    camera.position = (Vector3){ 7.53425, 6.84932, -11.6438 };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 3.0f, 0.0f };
    camera.fovy = 60.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    Image noiseImage = GenImagePerlinNoise(1000, 1000, 10.0f, 10.0f, 7); 
    float falloffRadius = 500; // Parameters can be adjusted
    Color *pixels = LoadImageColors(noiseImage);

    for (int y = 0; y < 1000; y++) {
        for (int x = 0; x < 1000; x++) {
            Color pixel = pixels[y * 1000 + x];
        
            float scaleFactor = RadialFalloff(x, y, 1000/2, 1000/2, falloffRadius);
            
            // Apply the scale factor to each color channel
            pixel.r = (int)(pixel.r * scaleFactor);
            pixel.g = (int)(pixel.g * scaleFactor);
            pixel.b = (int)(pixel.b * scaleFactor);
            if(pixel.r < 15 && pixel.g <15  && pixel.b < 15 ){
                pixel.a = 0;

            }
            pixel.a = (int)(pixel.a * scaleFactor);
            // Update the pixel back to the array
            pixels[y * 1000 + x] = pixel;
            ImageDrawPixel(&noiseImage, x, y, pixels[y * 1000 + x]); 
        }
    }

    ImageFormat(&noiseImage, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
    Texture2D texture = LoadTextureFromImage(noiseImage); 
    UnloadImageColors(pixels);

    Mesh mesh = GenMeshHeightmap(noiseImage, (Vector3){ 10, 10, 10 }); 
    Model model = LoadModelFromMesh(mesh);                  
    model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
    Vector3 mapPosition = { -5, 0, -5 };           
    UnloadImage(noiseImage);     
    std::cout<<screenHeight;
    std::cout<<screenWidth;
    SetTargetFPS(60);              
    std::cout << "screenHeight: " << screenHeight << std::endl;
    std::cout << "screenWidth: " << screenWidth << std::endl;

        // Initialize sliders for camera position
    float camX = 7.53425;
    float camY =  6.84932;
    float camZ = -11.6438 ;
        
    struct TextInfo {
        const char* text;
        int x;
        int y;
        int fontSize;
    };

    TextInfo texts[] = {
        {"BubbleSort", 82, 757, 20},
        {"MergeSort", 250, 757, 20},
        // Add more texts here if needed
    };

    int numTexts = sizeof(texts) / sizeof(texts[0]);

    BubbleSort Bubble_Sorting = BubbleSort(40);
    MergeSort Merge_Sorting = MergeSort(40);

    while (!WindowShouldClose())    
    {
        // Update camera position based on slider values
        camera.position = (Vector3){ camX, camY, camZ };

        // Drawing
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawRectangle(0, 0, screenWidth, screenHeight / 1.5, LIGHTGRAY);
        // Draw GUI Sliders
        GuiSlider((Rectangle){ 100, 100, 600, 20 }, "Camera X", NULL, &camX, -100.0f, 100.0f);
        GuiSlider((Rectangle){ 100, 140, 600, 20 }, "Camera Y", NULL, &camY, 0.0f, 100.0f);
        GuiSlider((Rectangle){ 100, 180, 600, 20 }, "Camera Z", NULL, &camZ, -100.0f, 100.0f);

        // Draw 3D Model and Grid
        BeginMode3D(camera);
            
            DrawModel(model, mapPosition, 1.0f, GRAY);
            //DrawGrid(20, 1.0f);
        EndMode3D();

        std::ostringstream positionStream;
        positionStream << "Camera Position: X: " << camX << ", Y: " << camY << ", Z: " << camZ;

        for (int i = 0; i < numTexts; i++) {
            bool hovering = IsMouseOverText(texts[i].text, texts[i].x, texts[i].y, texts[i].fontSize);

            // Change text color or style based on hover
            if (hovering) {
                DrawText(texts[i].text, texts[i].x, texts[i].y, texts[i].fontSize, BLUE); // Hover color
                DrawLine(texts[i].x, texts[i].y + texts[i].fontSize, texts[i].x + MeasureText(texts[i].text, texts[i].fontSize), texts[i].y + texts[i].fontSize, BLUE); // Underline
            } else {
                DrawText(texts[i].text, texts[i].x, texts[i].y, texts[i].fontSize, BLACK); // Default color
            }

            // If clicked on the text, call the corresponding update function
            if (hovering && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                if (i == 0) {
                    Bubble_Sorting.Update(); // Call bubble sort update
                } else if (i == 1) {
                    Merge_Sorting.Update(); // Call merge sort update
                }
                // Add more sorting algorithms if needed
            }
        }
        DrawText(positionStream.str().c_str(), 40, 50, 25, BLACK);
        //DrawText("BubbleSort",82,757,20,BLACK); 
        
        DrawFPS(10, 10);

        EndDrawing();
    }
    UnloadModel(model);     

    CloseWindow();              

    return 0;
}