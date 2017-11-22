//
// Created by giwiro on 11/20/17.
//

#ifndef CELEBRITY_FISHY_FACES_DETECT_H
#define CELEBRITY_FISHY_FACES_DETECT_H

#include <opencv2/core/core.hpp>
#include <opencv2/objdetect.hpp>

extern cv::CascadeClassifier cascadeClassifier;

void initialize_clasifier(std::string path);
std::vector<cv::Rect_<int>> detect_faces(cv::Mat image);
cv::Mat print_faces(const std::vector<cv::Rect_<int>> faces, const cv::Mat image);

#endif //CELEBRITY_FISHY_FACES_DETECT_H
