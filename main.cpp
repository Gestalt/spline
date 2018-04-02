#include <iostream>
#include <fstream>

#include "Spline.h"
#include "TableBasedFunction.h"
#include "Interpolation.h"
#include "InterpolationFactory.h"

int main(int argc, char** argv) {
    try {
        TableBasedFunction function;

        function.appendPoint(Point(0.f, 0.f));
        function.appendPoint(Point(1.f, 1.f));
        function.appendPoint(Point(2.f, 4.f));
        function.appendPoint(Point(3.f, 9.f));
        function.appendPoint(Point(4.f, 16.f));
        function.appendPoint(Point(5.f, 25.f));

        Interpolation* interpolation = InterpolationFactory::create(std::string("Neighbor"));
        Spline spline(interpolation);

        std::cout << spline.interpolate(&function, 2.2f) << std::endl;
    } catch (...) {
        std::cout << "err" << std::endl;
    }

    std::ifstream inn;
    std::ofstream out;

    inn.open("input.txt", std::ifstream::in);
    out.open("output.txt", std::ofstream::out);

    int n = 0;
    inn >> n;

    std::cout << "n=" << n << std::endl;

    //std::vector

    while(!inn.eof()) {
        float x;
        float y ;
        inn >> x >> y;

        std::cout << "x=" << x << " y=" << y << std::endl;
        out << x << " " << y << std::endl;
    }

    inn.close();
    out.close();

    std::cout << std::endl;

	return 0;
}
