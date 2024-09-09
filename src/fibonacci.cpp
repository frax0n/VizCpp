#include <vector>
#include "fibonacci.h"
#include "utils.h"
#include <random>
#include <chrono>
#include <thread>
#include "raygui.h"

Fibonacci :: Fibonacci(int number){
    this->number = number;
}

void Fibonacci::DrawFibonacciRecursively(int n, int x, int y, int offsetX, int offsetY) {
    if (n < 0) return; 

    DrawCircle(x, y, 20, Fade(DARKBLUE, 0.5f));  
    DrawText(TextFormat("Fib(%d)", n), x - 15, y - 10, 10, RAYWHITE);



    if (n > 1) {
        int leftX = x - offsetX;   
        int rightX = x + offsetX;  
        int nextY = y + offsetY;   

        DrawLine(x, y, leftX, nextY, BLACK);   
        DrawLine(x, y, rightX, nextY, BLACK);  

        DrawFibonacciRecursively(n - 1, leftX, nextY, offsetX / 2, offsetY);  // Fib(n-1)
        DrawFibonacciRecursively(n - 2, rightX, nextY, offsetX / 2, offsetY); // Fib(n-2)
    }
}

void Fibonacci :: Update(){

        // Slider to change Fibonacci number count
    //this->number = GuiSliderBar((Rectangle){ 10, 10, 150, 20 }, "Number", "", number, 1, 10);
    


}


void Fibonacci :: Draw(){
    this->DrawFibonacciRecursively(number, 400, 100, 150, 80);  
}