#include <vector>
#include <assert.h>

#include "QuadricInterpolation.h"
#include "LagrangePolynom.h"
#include "TableBasedFunction.h"
#include "Point.h"

const float QuadricInterpolation::interpolate(const sp::shared_ptr<TableBasedFunction>& function, float argument) const {
    if (!function) {
        assert(false);
        return 0.f;
    }
    //const std::vector<Point>& points = function->getPoints();
    const std::vector<Point> res = function->getNearestPoints(argument, 3);

    if (!res.empty()) {
        assert(res.size() == 3);
        return LagrangePolynom::solve(res, argument, 2);
    }

    assert(false);

    return 0.f;
}
