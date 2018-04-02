#include <vector>
#include <assert.h>

#include "LinearInterpolation.h"
#include "TableBasedFunction.h"
#include "Point.h"

const float LinearInterpolation::interpolate(TableBasedFunction* function, float argument) const {
    if (!function) {
        assert(false);
        return 0.f;
    }
    const std::vector<Point>& points = function->getPoints();
    const std::vector<Point> res = function->getNearestPoints(argument, 2);

    if (!res.empty()) {
        assert(res.size() == 2);

        float x = argument;

        float x0 = res[0].x;
        float x1 = res[1].x;

        float y0 = res[0].y;
        float y1 = res[1].y;

        float c = (x - x0) / (x1 - x0);

        float y = y0 * (1 - c) + y1 * c;

        return y;
    }

    assert(false);

    return 0.f;
}
