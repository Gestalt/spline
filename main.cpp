#include <iostream>
#include <fstream>
#include <vector>

#include "Spline.h"
#include "TableBasedFunction.h"
#include "Interpolation.h"
#include "InterpolationFactory.h"

static void loadFunctionFromFile(TableBasedFunction& function, std::string fileName) {
    std::ifstream inn;
    inn.open(fileName.c_str(), std::ifstream::in);

    int n = 0;
    inn >> n;

    std::cout << "n=" << n << std::endl;

    while(!inn.eof()) {
        float x;
        float y ;
        inn >> x >> y;

        std::cout << "x=" << x << " y=" << y << std::endl;

        function.appendPoint(Point(x, y));
    }
    inn.close();
}

static void loadArgumentsFromFile(std::vector<float>& args, std::string fileName) {
    std::ifstream inn;
    inn.open(fileName.c_str(), std::ifstream::in);

    int n = 0;
    inn >> n;

    std::cout << "n=" << n << std::endl;

    args.reserve(n);

    while(!inn.eof()) {
        float arg;
        inn >> arg;

        std::cout << "arg=" << arg << std::endl;

        args.push_back(arg);
    }

    inn.close();
}

int main(int argc, char** argv) {
    try {
        TableBasedFunction function;
        std::vector<float> args;

        loadFunctionFromFile(function, std::string("src.txt"));
        loadArgumentsFromFile(args, std::string("dest.txt"));

        Interpolation* interpolation = InterpolationFactory::create(std::string("Linear"));
        Spline spline(interpolation);

        std::ofstream out;
        out.open("output.txt", std::ofstream::out);

        for (std::vector<float>::const_iterator it = args.begin(); it != args.end(); ++it) {
            const float arg = *it;
            const float res = spline.interpolate(&function, arg);
//            out.precision(10);
//            out.setf( std::ios::fixed, std:: ios::floatfield );
            out << arg << " " << res << std::endl;
        }
        out.close();
    } catch (...) {
        std::cout << "err" << std::endl;
    }

    std::cout << std::endl;

	return 0;
}
