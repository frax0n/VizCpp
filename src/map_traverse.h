#pragma once
#include <vector>
#include <raylib.h>
#include "utils.h"

class utils;

class MapTraverse
{
    public:
    MapTraverse();
    void Update();
    void Draw();

    private:
    int grid_height;
    int grid_width ;
    bool close;


};