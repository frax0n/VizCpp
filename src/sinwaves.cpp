#include <vector>
#include <math.h>
#include "sinwaves.h"
#include <raylib.h>
#include <iostream>

SinWaves :: SinWaves(int screenWidth,int screenHeight,float angle,Color color){
    this->screenWidth  = screenWidth;
    this->screenHeight = screenHeight;
    this->angle        = angle;
    this->sinTheta     = sin(angle); 
    this->cosTheta     = cos(angle); 
    this->color        = color;
    speed = 2.0f;
    std::cout<<"Initialized Sinwaves";
}

void SinWaves :: Draw(int x,int y,Color color){
    DrawPixel(x,y,color);
}

void SinWaves :: Update(int xshift, int yshift,Color color){
    time += GetFrameTime() * speed;
    if(this->x_axis_initial < this->screenWidth){
        //this->time += GetFrameTime() * this->speed;
        this->x_axis_initial += 10;

        for(int i = 0;i<this->x_axis_initial*1.5;i++)
        {
            int y_axis = static_cast<int>((this->screenHeight / 2) + 50 * sin((i * 0.02)*0.21+time));
            float translatedX = i - this->screenWidth / 2;
            float translatedY = y_axis - this->screenHeight / 2;
            float rotatedX = translatedX * cosTheta - translatedY * sinTheta;
            float rotatedY = translatedX* sinTheta + translatedY * cosTheta; 
            rotatedX += this->screenWidth / 2;
            rotatedY += this->screenHeight / 2;
            this->Draw(rotatedX+xshift ,rotatedY+yshift,color);
        }
    }
    else{
            //this->time += GetFrameTime() * this->speed;
            for(int i = 0;i<this->x_axis_initial*1.5;i++){
            int y_axis = static_cast<int>((this->screenHeight / 2) + 50 * sin((i * 0.02)*0.21+time)); 
            float translatedX = i - this->screenWidth / 2;
            float translatedY = y_axis - this->screenHeight / 2;
            float rotatedX = translatedX * cosTheta - translatedY * sinTheta;
            float rotatedY = translatedX* sinTheta + translatedY * cosTheta; 
            rotatedX += this->screenWidth / 2;
            rotatedY += this->screenHeight / 2;
            this->Draw(rotatedX+xshift ,rotatedY+yshift,color);
        }
    }
}