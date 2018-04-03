#include <algorithm>
#include <assert.h>
#include "TableBasedFunction.h"

static bool sortPointsPredicate(const Point& lhs, const Point& rhs) {
    return lhs.x < rhs.x;
}

TableBasedFunction::TableBasedFunction(int numOfPoints)
    : points(std::vector<Point>()) {
    if (numOfPoints != 0) {
        points.reserve(numOfPoints);
    }
}

const std::vector<Point>& TableBasedFunction::getPoints() const {
    return points;
}

void TableBasedFunction::appendPoint(const Point& point) {
    if (!points.empty() && point.x <= points.back().x) {
        throw std::exception();
    }
    points.push_back(point);
}

const std::vector<Point> TableBasedFunction::getNearestPoints(float arg, int N) const {
//check for 0 size
    int size = points.size();

    if (N > size) {
        throw std::exception();
    }

    if (arg < points.front().x) {
        throw std::exception();
    }

    if (arg > points.back().x) {
        throw std::exception();
    }

    int index = -1;
    for (int i = 0; i < size; i++) {
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
        if (L >= 0 && L < size) {
            res.push_back(points[L]);
        }

        if (res.size() >= N) {
            break;
        }

        if (R >= 0 && R < size) {
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
