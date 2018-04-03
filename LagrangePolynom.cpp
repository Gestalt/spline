#include "LagrangePolynom.h"
#include "Point.h"

static float solveLagrangeCoefficient(const std::vector<Point>& function, float argument, int order, int coefficient) {
    float res = 1.f;

    unsigned int size = function.size();

    if (order > size || coefficient > size) {
        throw std::exception();
    }

    for (int i = 0; i <= order; i++) {
        if (i != coefficient) {
            const float x = argument;
            const float xi = function[i].x;
            const float xj = function[coefficient].x;

            if (xj == xi) {
                throw std::exception();
            }
            res *= (x - xi) / (xj - xi);
        }

    }

    return res;
}

float LagrangePolynom::solve(const std::vector<Point>& function, float argument, int order) {
    float res = 0.f;

    unsigned int size = function.size();

    if (order > size) {
        throw std::exception();
    }

    for (int i = 0; i <= order; i++) {
        res += function[i].y * solveLagrangeCoefficient(function, argument, order, i);
    }

    return res;
}
