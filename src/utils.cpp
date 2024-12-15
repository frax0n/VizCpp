#include "utils.h"
#include <vector>
#include <raylib.h>

void utils::Draw2dArray(std::vector<int> &array,int size){
    const int screenWidth = GetScreenWidth();
    const int screenHeight =  GetScreenHeight();

    float rectWidth = (screenWidth - 200 - (1*size))/size;
    int rectHeigthMultiplier = (screenHeight-200)/500;

    for (int i = 0; i<size; i++){
        float x = 200 + i * (rectWidth + 1);
        int y = 800 - array[i] * rectHeigthMultiplier;

        DrawRectangle(x,y,rectWidth,array[i]*rectHeigthMultiplier,BLUE);
        
    }

}

bool utils::IsMouseOverText(const char* text, int posX, int posY, int fontSize) {
    Vector2 textSize = MeasureTextEx(GetFontDefault(), text, fontSize, 1);
    Vector2 mousePosition = GetMousePosition();

    return (mousePosition.x >= posX && mousePosition.x <= posX + textSize.x &&
            mousePosition.y >= posY && mousePosition.y <= posY + textSize.y);
}