#include <algorithm>
#include <assert.h>
#include "Point.h"
#include "TableBasedFunction.h"
#include "InterpolationException.h"

static bool sortPointsPredicate(const Point& lhs, const Point& rhs) {
    return lhs.x < rhs.x;
}

TableBasedFunction::TableBasedFunction(int numOfPoints)
    : points(std::vector<Point>()) {
        if (numOfPoints != 0) {
            points.reserve(numOfPoints);
    }
}

void TableBasedFunction::appendPoint(const Point& point) {
    if (!points.empty() && point.x <= points.back().x) {
        throw InterpolationException(
            "Attempt to add an invalid argument. Unique arguments must be sorted in increasing order"
        );
    }
    points.push_back(point);
}

const std::vector<Point> TableBasedFunction::getNearestPoints(float arg, unsigned int N) const {
    size_t size = points.size();

    if (N > size) {
        throw InterpolationException(
            "Not enough points were specified to find required nearest arguments count"
        );
    }

    if (arg < points.front().x || arg > points.back().x) {
        throw InterpolationException(
            "Attempt to interpolate an argument outside of the specified range"
        );
    }

    int index = -1;
    for (size_t i = 0; i < size; i++) {
        if (arg < points[i].x) {
            break;
        } else {
            index = i;
        }
    }

    assert(index != -1);

    std::vector<Point> res;

    int L = index;
    int R = index + 1;

    float half = 0.5f * (points[L].x + points[R].x);

    if (arg >= half) {
        std::swap(L, R);
    }

    while (true) {
        if (L >= 0 && L < (int)size) {
            res.push_back(points[L]);
        }

        if (res.size() >= N) {
            break;
        }

        if (R >= 0 && R < (int)size) {
            res.push_back(points[R]);
        }

        if (res.size() >= N) {
            break;
        }

        if (L > R) {
            L += 1;
            R -= 1;
        } else {
            L -= 1;
            R += 1;
        }
    }

    std::sort(res.begin(), res.end(), sortPointsPredicate);

    return res;
}
