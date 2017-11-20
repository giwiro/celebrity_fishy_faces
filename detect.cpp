//
// Created by giwiro on 11/20/17.
//

#include "detect.h"
#include <iostream>

cv::CascadeClassifier cascadeClassifier;

void initialize_clasifier(std::string path) {
    cascadeClassifier.load(path);
    std::cout << "[Cascade Classifier]: initialized" << std::endl;
}

std::vector<cv::Rect_<int>> detect_faces() {

    // cascadeClassifier.detectMultiScale();
}