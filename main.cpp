#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>
#include <getopt.h>

#include "detect.h"
#include "options.h"

const static std::string BINARY_NAME = "celebrity_fishy_faces";

int main(int args, char *argv[]) {
    std::string haar_path;

    parse_options(args, argv, haar_path);
    initialize_clasifier(haar_path);

    const char *path = "/home/giwiro/CLionProjects/celebrity-fishy-faces/thumbnails_features_deduped_sample/adrien brody/1.jpg";

    cv::Mat image = cv::imread(path);
    if (!image.empty()) {
        std::vector<cv::Rect_<int>> faces = detect_faces(image);
        cv::Mat f = print_faces(faces, image);
        cv::imshow("image", f);
        cv::waitKey(0);
    }else {
        std::cout << "no hay imagen csv" << std::endl;
    }

    return 0;
}