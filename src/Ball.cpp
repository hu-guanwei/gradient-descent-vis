#include "Ball.h"
#include <iostream>
#include <mutex>
#include <thread>
#include <cmath>

Ball::Ball(int i, int j, int height, int width): _i(i), _j(j), _width(width), _height(height) {}
Ball::~Ball(){}

void Ball::simulate(std::mutex &mu) {
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        float x = _i * 2.0 / _height - 1;
        float y = _j * 2.0 / _width - 1;
        auto dx = x;
        auto dy = y;
        float lr = 1e-1;
        x -= lr * dx;
        y -= lr * dy;

        this->_i = static_cast<int>((x + 1) * _height / 2);
        this->_j = static_cast<int>((y + 1) * _width / 2);
        
        // if (pow(dx, 2) + pow(dy, 2) < 1e-3) {
        //     break;
        // }
       
        mu.lock();
        std::cout << "thread id\t: ";
        std::cout << std::this_thread::get_id() << std::endl;
        std::cout << "gradient norm\t: ";
        std::cout << sqrt(pow(dx, 2) + pow(dy, 2)) << std::endl; 
        std::cout << "===================================" << std::endl;
        mu.unlock();       
    }
}

