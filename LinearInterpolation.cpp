#include <vector>
#include <assert.h>

#include "LinearInterpolation.h"
#include "LagrangePolynom.h"
#include "TableBasedFunction.h"
#include "Point.h"

const float LinearInterpolation::interpolate(TableBasedFunction* function, float argument) const {
    if (!function) {
        assert(false);
        return 0.f;
    }
    //const std::vector<Point>& points = function->getPoints();
    const std::vector<Point> res = function->getNearestPoints(argument, 2);

    if (!res.empty()) {
        assert(res.size() == 2);

        return LagrangePolynom::solve(res, argument, 1);
    }

    assert(false);

    return 0.f;
}
