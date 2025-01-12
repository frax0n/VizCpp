#pragma once
#include <vector>
#include <raylib.h>

class RandomTraverse{
    public:
        RandomTraverse(int seed,int length);
        void Draw();
        void TranverseSeedMod();
        void TranverseLCG();
        int PointDistance(Vector2 point1,Vector2 point2);

    private:
        double seed;
        int length;
        std::vector<Vector2> points;
        bool skipIteration;
        int turnAroundCount = 0;
        int screenHeight;
        int screenWidth;

};