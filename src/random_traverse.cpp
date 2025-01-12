#include "random_traverse.h"
#include <raylib.h>
#include <vector>
#include <iostream>
#include <math.h>
#include <chrono>
#include <thread>
#include <random>

RandomTraverse :: RandomTraverse(int seed,int length){
    this->seed = seed;
    this->length = length;
    this->points.push_back({(float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2}); 
    this->turnAroundCount = 0;
    this->screenHeight = GetScreenHeight();
    this->screenWidth = GetScreenWidth();

}

int RandomTraverse :: PointDistance(Vector2 a,Vector2 b){
    return std::sqrt(abs((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y)));
};

void RandomTraverse :: Draw(){
    
    for (size_t i = 1; i < points.size(); ++i) {
        int psuedoLength = PointDistance(this->points[i - 1],this->points[i]);
        int distCentre = PointDistance({screenWidth/2,screenHeight/2},this->points[i-1]);
        if((psuedoLength > this->length+100 )|| (distCentre>380)){
            this->skipIteration  = true;
            continue;
        }
        DrawLineEx(this->points[i - 1],this->points[i],2,GRAY); 
        DrawCircle(this->points[i-1].x,this->points[i-1].y,2.0,DARKGRAY);
    }

};

void RandomTraverse :: TranverseSeedMod(){
    double randomNumber = static_cast<int>((this->seed * this->seed)) % 9973;
    double rand = randomNumber;
    randomNumber = static_cast<int>(randomNumber) % 360;

    Vector2 point = this->points.back();
    float x = point.x;
    float y = point.y;

    float rad = randomNumber * (PI / 180.0f);
    float newX = x + (length * cos(rad));
    float newY = y + (length * sin(rad));

    newX = static_cast<int>(newX + screenWidth) % screenWidth;
    newY = static_cast<int>(newY + screenHeight) % screenHeight;
    std::cout<<randomNumber<<" ";
    this->points.push_back({newX, newY});
    this->seed = static_cast<double>(rand);
    std::this_thread::sleep_for(std::chrono::milliseconds(25));

    this->Draw();
}

void RandomTraverse :: TranverseLCG(){

    int a = 16645; 
    int c = 101390; 
    int m = 42949; 

    long long result = static_cast<long long>(a) * this->seed + c; 

    long long modResult = result % m;

    
    if (modResult > INT_MAX) {
        modResult -= m;  
    }
    double randomNumber = static_cast<int>(modResult);

    //double randomNumber = static_cast<int>((this->seed * this->seed)) % 9973;
    randomNumber = static_cast<int>(randomNumber) % 360;

    Vector2 point = this->points.back();
    float x = point.x;
    float y = point.y;

    float rad = randomNumber * (PI / 180.0f);
    float newX = x + (length * cos(rad));
    float newY = y + (length * sin(rad));

    newX = static_cast<int>(newX + screenWidth) % screenWidth;
    newY = static_cast<int>(newY + screenHeight) % screenHeight;
    std::cout<<randomNumber<<" ";
    this->points.push_back({newX, newY});
    this->seed = static_cast<double>(modResult);
    std::this_thread::sleep_for(std::chrono::milliseconds(25));

    this->Draw();
}

