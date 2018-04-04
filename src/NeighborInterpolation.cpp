#include <vector>
#include <assert.h>

#include "NeighborInterpolation.h"
#include "TableBasedFunction.h"
#include "Point.h"

static const unsigned int kNeighborRequiredNearestPoints = 1;

const float app::NeighborInterpolation::interpolate(const sp::shared_ptr<TableBasedFunction>& function, float argument) const {
    if (!function) {
        assert(false);
        return 0.f;
    }
    const std::vector<Point> res = function->getNearestPoints(argument, kNeighborRequiredNearestPoints);

    if (!res.empty()) {
        return res.front().y;
    }

    assert(false);

    return 0.f;
}
