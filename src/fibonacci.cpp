#pragma once
#include <vector>
#include "fibonacci.h"
#include "utils.h"
#include <random>
#include <chrono>
#include <thread>





int fibonacci(int n, int& Depth, bool& Depth_reverse) {
    if (n == 1) {
        Depth_reverse = true;
        return 1;
    }
    if (n == 0) {
        return 1;
    }

    if (Depth_reverse) {
        Depth -= 1;
    } else {
        Depth += 1;
    }

    int leftDepth = Depth;
    bool leftReverse = Depth_reverse;
    int rightDepth = Depth;
    bool rightReverse = Depth_reverse;

    return fibonacci(n - 1, leftDepth, leftReverse) + fibonacci(n - 2, rightDepth, rightReverse);
}
