#pragma once

#include <opencv2/core.hpp>
#include <functional>
#include <memory>
#include <vector>
#include "Ball.h"

class Graphics {
private:
    cv::Mat _landscape;
    int _width;
    int _height;
    std::vector<std::shared_ptr<Ball>> _balls;
public:
    Graphics() = delete;
    Graphics(int height, int width);
    ~Graphics();
    void simulate(const char *windowName);
    void fillLandscapeWith(const std::function<float(float, float)> &f);
    void setBalls(std::vector<std::shared_ptr<Ball>> &balls);
    std::vector<std::shared_ptr<Ball>> getBalls();
};


