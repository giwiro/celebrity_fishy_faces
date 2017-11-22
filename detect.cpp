//
// Created by giwiro on 11/20/17.
//

#include "detect.h"
#include <iostream>

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

cv::CascadeClassifier cascadeClassifier;

void initialize_clasifier(std::string path) {
    std::cout << "[Cascade Classifier]: path: " << path << std::endl;
    cascadeClassifier.load(path);
    std::cout << "[Cascade Classifier]: initialized" << std::endl;
}

std::vector<cv::Rect_<int>> detect_faces(cv::Mat image) {
    cv::Mat gray;
    std::vector< cv::Rect_<int> > faces;
    cv::cvtColor(image, gray, CV_BGR2GRAY);
    cascadeClassifier.detectMultiScale(gray, faces);
    return faces;
}

// TODO: Take care of memory management -> cloning a cv::Mat
cv::Mat print_faces(const std::vector<cv::Rect_<int>> faces, const cv::Mat image) {
    cv::Mat f = image.clone();
    for (int i = 0; i < faces.size(); i++) {
        cv::Rect face_i = faces[i];
        cv::rectangle(f, face_i, cv::Scalar(0, 0, 255), 2);
    }
    return f;
}