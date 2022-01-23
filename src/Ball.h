#pragma once

#include <thread>
#include <vector>
#include <mutex>
#include <condition_variable>


class Ball {
private:
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
    int getI() {
        return _i;
    }
    int getJ() {
        return _j;
    }
    void setI(int i) {this->_i = i;}
    void setJ(int j) {this->_j = j;}
    ~Ball();
};