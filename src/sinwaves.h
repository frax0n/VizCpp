#pragma once
#include <vector>
#include <raylib.h>
#include <math.h>


class SinWaves{
    public:
        SinWaves(int screenWidth,int screenHeight,float angle,Color color);
        void Update(int xshift, int yshift,Color color);
        void Draw(int x,int y,Color color);

    private:
        int screenWidth;
        int screenHeight;
        Color color;
        float x_axis_initial = 0;
        float speed;
        float time;
        float angle;
        float cosTheta;
        float sinTheta;

};