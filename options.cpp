//
// Created by giwiro on 11/21/17.
//

#include "options.h"
#include <iostream>
#include <getopt.h>

const static std::string BINARY_NAME = "celebrity_fishy_faces";

static void show_usage() {
    std::cerr << "Usage: " << BINARY_NAME << "\n\n"
              << "Options:\n"
              << "\t-h, --help\t\t\t\tPrint argument list\n"
              << "\t-f, --haar-file\t\t\tPath to haar cascade trained file\n"
              << std::endl;
}

void parse_options(int args, char *argv[], std::string &haar_path) {
    int f_help = 0;

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
        exit(0);
    }

    if (!haar_path.size()) {
        std::cerr << "No haardcascade file provided" << std::endl;
        exit(1);
    }

}