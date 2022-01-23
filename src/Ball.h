#pragma once

#include <thread>
#include <vector>
#include <mutex>
#include <condition_variable>


class Ball {
public:
    // posion in grid
    int _i;
    int _j;

    // gird width and height
    int _width;
    int _height;
public:
    void simulate(std::mutex &mu);
    Ball() = delete;
    Ball(int i, int j, int height, int width);
    ~Ball();
};