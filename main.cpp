#include <iostream>
#include "Application.h"
#include "Parameters.h"
#include "InterpolationException.h"

static void help() {
    std::cout <<
        "      \n" <<
        "Usage:\n" <<
        "      --source|-s        file source with function points\n" <<
        "      --destination|-d   file source with arguments to be interpolated\n" <<
        "      --output|-o        output file. Default is <output.txt>\n" <<
        "      --verbose|-v       be verbose\n" <<
        "      --help|-h          print this message\n" <<
    std::endl;
}

int main(int argc, char** argv) {
    Parameters params;

    try {
        const std::string err = params.parse(argc, argv);
        if (!err.empty()) {
            std::cout << err << std::endl;
            help();
            return 0;
        }
        processInterpolation(params);
    } catch (const InterpolationException& ex) {
        std::cout << "An interpolation exception occured. " << ex.what() << std::endl;
    } catch (const std::exception& ex) {
        std::cout << "An exception occured. " << ex.what() << std::endl;
    } catch (...) {
        std::cout << "An unknown  exception occured" << std::endl;
    }
	return 0;
}