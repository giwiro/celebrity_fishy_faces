//
// Created by giwiro on 11/20/17.
//

#include "detect.h"
#include <iostream>

#include <opencv2/imgproc/imgproc.hpp>

cv::CascadeClassifier cascadeClassifier;

void initialize_clasifier(std::string path) {
    cascadeClassifier.load(path);
    std::cout << "[Cascade Classifier]: initialized" << std::endl;
}

std::vector<cv::Rect_<int>> detect_faces(cv::Mat image) {
    cv::Mat gray;
    cv::cvtColor(image, gray, CV_BGR2GRAY);
    // cascadeClassifier.detectMultiScale();
}