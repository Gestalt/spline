#include <iostream>
#include "Application.h"
#include "InputFile.h"
#include "OutputFile.h"
#include "Parameters.h"
#include "Spline.h"
#include "TableBasedFunction.h"
#include "Interpolation.h"
#include "InterpolationFactory.h"

static void loadFunctionFromFile(TableBasedFunction& function, std::string fileName) {
    InputFile file(fileName);
    std::istream& stream = file.stream();

    int n = 0;
    stream >> n;

    std::cout << "n=" << n << std::endl;

    while(!stream.eof()) {
        float x;
        float y;

        stream >> x;
        stream >> y;

        std::cout << "x=" << x << " y=" << y << std::endl;

        function.appendPoint(Point(x, y));
    }
}

static void loadArgumentsFromFile(std::vector<float>& args, std::string fileName) {
    InputFile file(fileName);
    std::istream& stream = file.stream();

    int n = 0;
    stream >> n;

    std::cout << "n=" << n << std::endl;

    args.reserve(n);

    while(!stream.eof()) {
        float arg;
        stream >> arg;

        std::cout << "arg=" << arg << std::endl;

        args.push_back(arg);
    }
}

void processInterpolation(const Parameters& params) {
    TableBasedFunction function;
    std::vector<float> args;

    loadFunctionFromFile(function, params.getSource());
    loadArgumentsFromFile(args, params.getDestination());

    Interpolation* interpolation = InterpolationFactory::create(params.getSpline());
    Spline spline(interpolation);

    OutputFile file(params.getOutput());
    std::ofstream& stream = file.stream();

    for (std::vector<float>::const_iterator it = args.begin(); it != args.end(); ++it) {
        const float arg = *it;
        const float res = spline.interpolate(&function, arg);
//            out.precision(10);
//            out.setf( std::ios::fixed, std:: ios::floatfield );
        stream << arg << " " << res << std::endl;
    }
}
