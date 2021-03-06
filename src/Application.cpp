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

static sp::shared_ptr<app::TableBasedFunction> createFunctionFromFile(std::string fileName) {
    app::InputFile file(fileName);
    std::istream& stream = file.stream();

    app::verbose() << "Loading function from: " << fileName;

    int n = 0;
    stream >> n;

    app::verbose() << "Total points count to append: " << n;

    sp::shared_ptr<app::TableBasedFunction> res = sp::make_shared<app::TableBasedFunction>(n);

    if (!res) {
        return sp::shared_ptr<app::TableBasedFunction>();
    }

    while(!stream.eof()) {
        float x;
        float y;

        stream >> x;
        stream >> y;

        app::verbose() << "Appending point (x,y): " << "(" << x << "," << y << ")";

        res->appendPoint(app::Point(x, y));
    }

    return res;
}

static void loadArgumentsFromFile(std::vector<float>& args, std::string fileName) {
    app::InputFile file(fileName);
    std::istream& stream = file.stream();

    app::verbose() << "Loading arguments from: " << fileName;

    int n = 0;
    stream >> n;

    app::verbose() << "Total arguments to append: " << n;

    args.reserve(n);

    while(!stream.eof()) {
        float arg;
        stream >> arg;

        app::verbose() << "Appending argument (x): " << arg;

        args.push_back(arg);
    }
}

void app::Application::process(const Parameters& params) {
    if (params.getVerbose()) {
        Logger::instance()->setLevel(Logger::verbose);
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
