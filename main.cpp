#include <opencv2/core/core.hpp>

#include <iostream>
#include <getopt.h>

#include "detect.h"

const static std::string BINARY_NAME = "celebrity_fishy_faces";

static void show_usage() {
    std::cerr << "Usage: " << BINARY_NAME << "\n\n"
              << "Options:\n"
              << "\t-h, --help\t\t\t\tPrint argument list\n"
              << "\t-f, --haar-file\t\t\tPath to haar cascade trained file\n"
              << std::endl;
}

int main(int args, char *argv[]) {

    int f_help = 0;
    std::string haar_path;

    struct option longopts[] = {
            {"help",            no_argument,                nullptr,        'h'},
            {"haar-file",       required_argument,          nullptr,        'f'},
            {nullptr,           0,                          nullptr,        0}
    };

    while (1) {
        int opt_index = 0;
        int opt_result = getopt_long(args, argv, "hf:",
                                     longopts, &opt_index);

        if (opt_result == -1) {
            break;
        }

        switch (opt_result) {
            case 'h':
                f_help = 1;
                break;
            case 'f':
                haar_path = optarg;
                break;
        }
    }

    if (f_help) {
        show_usage();
    }

    if (!haar_path.size()) {
        std::cerr << "No haardcascade file provided" << std::endl;
        return 1;
    }

    initialize_clasifier(haar_path);

    return 0;
}