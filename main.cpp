#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

#include "Parameters.h"
#include "Spline.h"
#include "TableBasedFunction.h"
#include "Interpolation.h"
#include "InterpolationFactory.h"

static void loadFunctionFromFile(TableBasedFunction& function, std::string fileName) {
    std::ifstream inn;
    inn.open(fileName.c_str(), std::ifstream::in);

    if (!inn.is_open()) {
        return;
    }

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

    if (!inn.is_open()) {
        return;
    }

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
    Parameters params;

    try {
        if (!params.parse(argc, argv)) {
            return 1;
        }

        TableBasedFunction function;
        std::vector<float> args;

        loadFunctionFromFile(function, params.getSource());
        loadArgumentsFromFile(args, params.getDestination());

        Interpolation* interpolation = InterpolationFactory::create(params.getSpline());
        Spline spline(interpolation);

        std::ofstream out;
        out.open(params.getOutput().c_str(), std::ofstream::out);

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
