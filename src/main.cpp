#include "Graphics.h"
#include "Ball.h"
#include <math.h>
#include <memory>
#include <vector>
#include <thread>
#include <iostream>
#include <random>

std::random_device rd;
std::mt19937 eng(rd());

int main() {
    int gridWidth = 1200;
    int gridHeight = 1200;
    std::uniform_int_distribution<> distr(0, std::max(gridHeight, gridWidth));

    // set up graphics
    Graphics g {gridHeight, gridWidth};
    g.fillLandscapeWith([](float x, float y) -> float{return (pow(x, 2) + pow(y, 2));});

    // set up rolling balls
    std::vector<std::shared_ptr<Ball>> balls;
    for (int i = 0; i < 50; i++) {
        // set each ball starts with a possibly different position
        auto initI = distr(eng) % gridHeight;
        auto initJ = distr(eng) % gridWidth;
        balls.emplace_back(std::make_shared<Ball>(initI, initJ, gridHeight, gridWidth));
    }
    g.setBalls(balls);
    std::vector<std::thread> ts;
    std::mutex mu;
    for (auto &b: balls) {
        // simulate each ball in a different thread
        ts.emplace_back(&Ball::simulate, b, std::ref(mu));
    }
    
    // simulation threads
    std::thread gThread = std::thread {
        &Graphics::simulate, 
        std::ref(g), 
        "Gradient Descent Visualization (press 'r' to rest, press 'q' to quit GUI)"
    };
    gThread.join();
    for (auto &t: ts) {
        t.join();
    }
}