#include <vector>
#include <assert.h>

#include "QuadricInterpolation.h"
#include "LagrangePolynom.h"
#include "TableBasedFunction.h"
#include "Point.h"

static const unsigned int kQuadricInterpolationPolynomOrder = 2;

const float QuadricInterpolation::interpolate(const sp::shared_ptr<TableBasedFunction>& function, float argument) const {
    if (!function) {
        assert(false);
        return 0.f;
    }
    const std::vector<Point> res = function->getNearestPoints(argument, kQuadricInterpolationPolynomOrder + 1);

    if (!res.empty()) {
        return LagrangePolynom::solve(res, argument, kQuadricInterpolationPolynomOrder);
    }

    assert(false);

    return 0.f;
}
