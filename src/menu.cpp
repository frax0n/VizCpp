// #include <vector>
// #include "menu.h"
// #include "utils.h"
// #include <thread>
// #include <sstream>
// #include <math.h>
// #include <iostream>
// #include "include/raygui.h" 

// Menu :: Menu(int size,int falloffRadius){

//     utils Custom_Utils = utils();
    
//     screenWidth = GetScreenWidth();
//     screenHeight =  GetScreenHeight();
//     std::vector<float> falloffValues(size * size);
//     for (int y = 0; y < size; y++) {
//     for (int x = 0; x < size; x++) {
//         falloffValues[y * size + x] = RadialFalloff(x, y, size/2, size/2, falloffRadius);
//     }
//     }
//     Camera camera = { 0 };
//     camera.position = (Vector3){ 7.53425, 6.84932, -11.6438 };
//     camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
//     camera.up = (Vector3){ 0.0f, 3.0f, 0.0f };
//     camera.fovy = 60.0f;
//     camera.projection = CAMERA_PERSPECTIVE;

//     utils::TextInfo texts[] = {
//         {"BubbleSort", 82, 757, 20},
//         {"MergeSort", 250, 757, 20},
//     };
//     Image noiseImage = GenImagePerlinNoise(size, size, 10.0f, 10.0f, 7); 
//      // Parameters can be adjusted
//     Color *pixels = LoadImageColors(noiseImage);
//     for (int y = 0; y < size; y++) {
//         for (int x = 0; x < size; x++) {
//             Color pixel = pixels[y * size + x];
        
//             float scaleFactor = falloffValues[y * size + x];
            
            
//             pixel.r = (int)(pixel.r * scaleFactor);
//             pixel.g = (int)(pixel.g * scaleFactor);
//             pixel.b = (int)(pixel.b * scaleFactor);
//             if(pixel.r < 15 && pixel.g <15  && pixel.b < 15 ){
//                 pixel.a = 0;

//             }
//             pixel.a = (int)(pixel.a * scaleFactor);

//             pixels[y * size + x] = pixel;
//             ImageDrawPixel(&noiseImage, x, y, pixels[y * size + x]); 
//         }
//     }
//     ImageFormat(&noiseImage, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
//     Texture2D texture = LoadTextureFromImage(noiseImage); 
//     UnloadImageColors(pixels);
//     growthFactor = 0.0f;   
//     growthSpeed = 0.02f; 
//     Mesh mesh = GenMeshHeightmap(noiseImage, (Vector3){ 10, 10, 10 }); 
//     model = LoadModelFromMesh(mesh); 
//     model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
               
//     UnloadImage(noiseImage);     
//     SetTargetFPS(72);              

//     utils::TextInfo texts[] = {
//         {"BubbleSort", 82, 757, 20},
//         {"MergeSort", 250, 757, 20},
//     };

//     numTexts = sizeof(texts) / sizeof(texts[0]);

//     std::vector<float> originalY(mesh.vertexCount);
//     for (int i = 0; i < mesh.vertexCount; i++) {
//         originalY[i] = mesh.vertices[i * 3 + 1];  
//     }

//     needsUpdate = true;
 

// }

// void Menu::Update(){
//     camera.position = (Vector3){ this->camX, this->camY, this->camZ };
//         if (this->growthFactor < 1.0f) {
//             this->growthFactor += this->growthSpeed;  
//             this->needsUpdate = true;           
//         } else {
//             this->needsUpdate = false;          
//         }
//         if (needsUpdate) {
//         for (int i = 0; i < this->mesh.vertexCount; i++) {
//         this->mesh.vertices[i * 3 + 1] = this->originalY[i] * this->growthFactor;  
//         this->camZ = this->startZ + (this->endZ - this->startZ) * growthFactor;
//         this->camera.position = (Vector3){ this->camX, this->camY, this->camZ };
//         }}
//         UpdateMeshBuffer(mesh, 0, mesh.vertices, mesh.vertexCount*3*sizeof(float),0);
//         // Drawing
//         BeginDrawing();
//         ClearBackground(RAYWHITE);
//         DrawRectangle(0, 0, screenWidth, screenHeight / 1.5, LIGHTGRAY);

//         GuiSlider((Rectangle){ 100, 100, 600, 20 }, "Camera X", NULL, &camX, -100.0f, 100.0f);
//         GuiSlider((Rectangle){ 100, 140, 600, 20 }, "Camera Y", NULL, &camY, 0.0f, 100.0f);
//         GuiSlider((Rectangle){ 100, 180, 600, 20 }, "Camera Z", NULL, &camZ, -100.0f, 100.0f);
 

//         BeginMode3D(camera);
            
//         DrawModel(model, mapPosition, 1.0f, GRAY);
//             //DrawGrid(20, 1.0f);
//         EndMode3D();
//         DrawRectangle(0, screenHeight / 1.5, screenWidth, screenHeight-(screenHeight / 1.5) , WHITE);
//         std::ostringstream positionStream;
//         positionStream << "Camera Position: X: " << camX << ", Y: " << camY << ", Z: " << camZ;

//         for (int i = 0; i < numTexts; i++) {
//             bool hovering = Custom_Utils.IsMouseOverText(texts[i].text, texts[i].x, texts[i].y, texts[i].fontSize);

//             // Change text color or style based on hover
//             if (hovering) {
//                 DrawText(texts[i].text, texts[i].x, texts[i].y, texts[i].fontSize, BLUE); // Hover color
//                 DrawLine(texts[i].x, texts[i].y + texts[i].fontSize, texts[i].x + MeasureText(texts[i].text, texts[i].fontSize), texts[i].y + texts[i].fontSize, BLUE); // Underline
//             } else {
//                 DrawText(texts[i].text, texts[i].x, texts[i].y, texts[i].fontSize, BLACK); // Default color
//             }


//             if (hovering && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
//                 if (i == 0) {
//                     BubbleSort Bubble_Sorting = BubbleSort(45);
//                     Bubble_Sorting.Update(); 
//                 } else if (i == 1) {
//                     MergeSort Merge_Sorting = MergeSort(70);
//                     Merge_Sorting.Update(); 
//                 }

//             }
//         }
//         DrawText(positionStream.str().c_str(), 40, 50, 25, BLACK);

        
//         DrawFPS(10, 10);

//         EndDrawing();
// }


// float Menu :: RadialFalloff(float x, float y, float centerX, float centerY, float radius)
// {
//     float distance = sqrt((x - centerX) * (x - centerX) + (y - centerY) * (y - centerY));
//     float normalizedDistance = distance / radius;
//     if (normalizedDistance > 1.0f) normalizedDistance = 1.0f;
//     return (1.0f - normalizedDistance) * (1.0f - normalizedDistance);
// }

