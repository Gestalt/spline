#include <iostream>
#include "Application.h"
#include "InputFile.h"
#include "OutputFile.h"
#include "Parameters.h"
#include "Spline.h"
#include "TableBasedFunction.h"
#include "Interpolation.h"
#include "InterpolationFactory.h"
#include "Defs.h"

static sp::shared_ptr<TableBasedFunction> createFunctionFromFile(std::string fileName) {
    InputFile file(fileName);
    std::istream& stream = file.stream();

    int n = 0;
    stream >> n;

    std::cout << "n=" << n << std::endl;

    sp::shared_ptr<TableBasedFunction> res = sp::make_shared<TableBasedFunction>(n);

    if (!res) {
        return sp::shared_ptr<TableBasedFunction>();
    }

    while(!stream.eof()) {
        float x;
        float y;

        stream >> x;
        stream >> y;

        std::cout << "x=" << x << " y=" << y << std::endl;

        res->appendPoint(Point(x, y));
    }

    return res;
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
    sp::shared_ptr<TableBasedFunction> function = createFunctionFromFile(params.getSource());

    std::vector<float> args;
    loadArgumentsFromFile(args, params.getDestination());

    sp::shared_ptr<Interpolation> interpolation = InterpolationFactory::instance()->create(params.getSpline());
    sp::shared_ptr<Spline> spline = sp::make_shared<Spline>(interpolation);

    OutputFile file(params.getOutput());
    std::ofstream& stream = file.stream();

    for (std::vector<float>::const_iterator it = args.begin(); it != args.end(); ++it) {
        const float arg = *it;
        const float res = spline->interpolate(function, arg);
//            out.precision(10);
//            out.setf( std::ios::fixed, std:: ios::floatfield );
        stream << arg << " " << res << std::endl;
    }
}
