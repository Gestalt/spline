#include <vector>
#include <assert.h>

#include "QuadricInterpolation.h"
#include "TableBasedFunction.h"
#include "Point.h"

const float QuadricInterpolation::interpolate(TableBasedFunction* function, float argument) const {
    if (!function) {
        assert(false);
        return 0.f;
    }
    const std::vector<Point>& points = function->getPoints();
    const std::vector<Point> res = function->getNearestPoints(argument, 3);

    if (!res.empty()) {
        assert(res.size() == 3);

        float x = argument;

        float x0 = res[0].x;
        float x1 = res[1].x;
        float x2 = res[2].x;

        float y0 = res[0].y;
        float y1 = res[1].y;
        float y2 = res[2].y;

        float c0 = ((x - x1) * (x - x2)) / ((x0 - x1) * (x0 - x2));
        float c1 = ((x - x0) * (x - x2)) / ((x1 - x0) * (x1 - x2));
        float c2 = ((x - x0) * (x - x1)) / ((x2 - x0) * (x2 - x1));

        float y = y0 * c0 + y1 * c1 + y2 * c2;

        return y;
    }

    assert(false);

    return 0.f;
}
