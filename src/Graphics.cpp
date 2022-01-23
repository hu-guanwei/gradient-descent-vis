#include "Graphics.h"
#include <opencv4/opencv2/core/matx.hpp>
#include <opencv4/opencv2/core/types.hpp>
#include <opencv4/opencv2/highgui.hpp>
#include <opencv4/opencv2/imgproc.hpp>
#include <iostream>
#include <memory>
#include <thread>
#include <random>

Graphics::Graphics(int height, int width): _width(width), _height(height) {
    this->_landscape = cv::Mat::zeros(height, width, CV_32F);
}

Graphics::~Graphics() {
}

void Graphics::simulate(const char *windowName) {
    cv::Mat landscapeNormalized, landscapeNormalizedCopy;

    cv::normalize(_landscape, landscapeNormalized, 0, 1, cv::NORM_MINMAX);
    landscapeNormalizedCopy = landscapeNormalized.clone();

    std::random_device rd;
    std::mt19937 eng(rd());
    std::uniform_int_distribution<> distr(0, std::max(_height, _width));

    while (true) {
        auto key = cv::waitKey(33);
        if (key == 'q') {
            break;
        }
        if (key == 'r') {
            // reset positions of balls
            for (auto &b: getBalls()) {
                b->setI(distr(eng) % _height);
                b->setJ(distr(eng) % _width);
            }
        }
        for (auto &b: getBalls()) {
            cv::circle(
                landscapeNormalized, 
                cv::Point(b->getI(), b->getJ()), 10, 
                cv::Scalar(255), -1, 
                cv::LINE_8);
        }
        cv::namedWindow(windowName, cv::WINDOW_NORMAL);
        cv::imshow(windowName, landscapeNormalized);
        cv::resizeWindow(windowName, cv::Size(this->_width, this->_height));
        landscapeNormalized = landscapeNormalizedCopy.clone();
    }
    cv::destroyAllWindows();
}
 
void Graphics::fillLandscapeWith(const std::function<float(float, float)> &f) {
    // set landscape values
    for (int i = 0; i < _height; i++) {
        for (int j = 0; j < _width; j++) {
            float x = i * 2.0 / _height - 1;
            float y = j * 2.0 / _width - 1;
            _landscape.at<float>(i, j) = f(x, y);
        }
    }
}

void Graphics::setBalls(std::vector<std::shared_ptr<Ball>> &balls) {
    this->_balls = balls;
}

std::vector<std::shared_ptr<Ball>> Graphics::getBalls() {
    return this->_balls;
}