#pragma once
#include <vector>
#include <raylib.h>

class utils {
public:
    struct TextInfo {
        const char* text;
        int x;
        int y;
        int fontSize;
    };
    
    void Draw2dArray(std::vector<int>& array, int size);
    bool IsMouseOverText(const char* text, int posX, int posY, int fontSize);
};


