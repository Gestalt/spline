#include "Application.h"
#include "InputFile.h"
#include "OutputFile.h"
#include "Parameters.h"
#include "Spline.h"
#include "TableBasedFunction.h"
#include "Interpolation.h"
#include "InterpolationFactory.h"
#include "Log.h"
#include "Defs.h"
#include "Point.h"

static sp::shared_ptr<TableBasedFunction> createFunctionFromFile(std::string fileName) {
    InputFile file(fileName);
    std::istream& stream = file.stream();

    verbose() << "Loading function from: " << fileName;

    int n = 0;
    stream >> n;

    verbose() << "Total points count to append: " << n;

    sp::shared_ptr<TableBasedFunction> res = sp::make_shared<TableBasedFunction>(n);

    if (!res) {
        return sp::shared_ptr<TableBasedFunction>();
    }

    while(!stream.eof()) {
        float x;
        float y;

        stream >> x;
        stream >> y;

        verbose() << "Appending point (x,y): " << "(" << x << "," << y << ")";

        res->appendPoint(Point(x, y));
    }

    return res;
}

static void loadArgumentsFromFile(std::vector<float>& args, std::string fileName) {
    InputFile file(fileName);
    std::istream& stream = file.stream();

    verbose() << "Loading arguments from: " << fileName;

    int n = 0;
    stream >> n;

    verbose() << "Total arguments to append: " << n;

    args.reserve(n);

    while(!stream.eof()) {
        float arg;
        stream >> arg;

        verbose() << "Appending argument (x): " << arg;

        args.push_back(arg);
    }
}

void Application::process(const Parameters& params) {
    if (params.getVerbose()) {
        Logger::instance()->setLevel(Logger::LogLevel::verbose);
    }

    sp::shared_ptr<TableBasedFunction> function = createFunctionFromFile(params.getSource());

    std::vector<float> args;
    loadArgumentsFromFile(args, params.getDestination());

    sp::shared_ptr<Interpolation> interpolation = InterpolationFactory::instance()->create(params.getSpline());
    sp::shared_ptr<Spline> spline = sp::make_shared<Spline>(interpolation);

    verbose() << "Interpolation is set to be: " << params.getSpline();

    OutputFile file(params.getOutput());
    std::ofstream& stream = file.stream();

    verbose() << "The interpolation results will be written to: " << params.getOutput();

    for (std::vector<float>::const_iterator it = args.begin(); it != args.end(); ++it) {
        const float arg = *it;
        const float res = spline->interpolate(function, arg);
        verbose() << "Interpolated value at x: " << arg << " is y: " << res;
        stream << arg << " " << res << std::endl;
    }
}
