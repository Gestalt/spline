#include <iostream>
#include "Application.h"
#include "Parameters.h"

static void help() {
    std::cout <<
        "Usage: \n" <<
        "--source|-s    set function file\n" <<
        "--destination|-d    set arguments file\n" <<
        "--output|-o    set output file\n" <<
        "--verbose|-v    be verbose\n" <<
        "--help|-h    print help\n" <<
    std::endl;
}

int main(int argc, char** argv) {
    Parameters params(help);

    try {
        if (!params.parse(argc, argv)) {
            return 1;
        }
        processInterpolation(params);
    } catch (...) {
        std::cout << "err" << std::endl;
    }

    std::cout << std::endl;

	return 0;
}
