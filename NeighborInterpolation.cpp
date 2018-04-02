#include <vector>
#include <assert.h>

#include "NeighborInterpolation.h"
#include "TableBasedFunction.h"
#include "Point.h"

const float NeighborInterpolation::interpolate(TableBasedFunction* function, float argument) const {
    if (!function) {
        assert(false);
        return 0.f;
    }
    const std::vector<Point>& points = function->getPoints();
    const std::vector<Point> res = function->getNearestPoints(argument, 1);

    if (!res.empty()) {
        return res.front().y;
    }

    assert(false);

    return 0.f;
}
