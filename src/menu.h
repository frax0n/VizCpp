#pragma once
#include <vector>
#include <raylib.h>
#include "utils.h"

class utils;

class Menu
{
    public:
    Menu(int size,int falloffRadius);
    void Update();
    void Draw();

    private:
    float RadialFalloff(float x, float y, float centerX, float centerY, float radius);
    std::vector<float> falloffValues;
    float falloffRadius;
    bool close;
    Camera camera;
    Image noiseImage;
    Color *pixels;
    Model model;
    Mesh mesh;
    float camX = 7.53425;
    float camY =  6.84932;
    float camZ = -11.6438 ;
    Vector3 mapPosition = { -5, 0, -5 };
    float growthFactor = 0.0f;      
    float growthSpeed = 0.02f;
    bool needsUpdate = false;
    float startZ =  10.274;
    float endZ = -11.6438 ;
    std::vector<float> originalY;
    int screenWidth;
    int screenHeight;
    int numTexts;
    
};