#include <vector>
#include <assert.h>

#include "LinearInterpolation.h"
#include "LagrangePolynom.h"
#include "TableBasedFunction.h"
#include "Point.h"

static const unsigned int kLinearInterpolationPolynomOrder = 1;

const float LinearInterpolation::interpolate(const sp::shared_ptr<TableBasedFunction>& function, float argument) const {
    if (!function) {
        assert(false);
        return 0.f;
    }
    const std::vector<Point> res = function->getNearestPoints(argument, kLinearInterpolationPolynomOrder + 1);

    if (!res.empty()) {
        return LagrangePolynom::solve(res, argument, kLinearInterpolationPolynomOrder);
    }

    assert(false);

    return 0.f;
}
