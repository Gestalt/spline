#include "LagrangePolynom.h"
#include "Point.h"
#include "InterpolationException.h"

static float solveLagrangeCoefficient(const std::vector<app::Point>& function, float argument, unsigned int order, unsigned int coefficient) {
    float res = 1.f;

    unsigned int size = function.size();

    if (order > size || coefficient > size) {
        throw app::InterpolationException(
            "Not enough points to resolve Lagrange coefficients"
        );
    }

    for (unsigned int i = 0; i <= order; i++) {
        if (i != coefficient) {
            const float x = argument;
            const float xi = function[i].x;
            const float xj = function[coefficient].x;

            if (xj == xi) {
                throw app::InterpolationException(
                    "Division by zero while resolving Lagrange polynom"
                );
            }
            res *= (x - xi) / (xj - xi);
        }
    }

    return res;
}

float app::LagrangePolynom::solve(const std::vector<Point>& function, float argument, unsigned int order) {
    float res = 0.f;

    unsigned int size = function.size();

    if (order > size) {
        throw InterpolationException(
            "Not enough points to resolve Lagrange polynom"
        );
    }

    for (unsigned int i = 0; i <= order; i++) {
        res += function[i].y * solveLagrangeCoefficient(function, argument, order, i);
    }

    return res;
}
