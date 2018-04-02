#include <algorithm>
#include <assert.h>
#include "TableBasedFunction.h"

bool sortPointsPredicate(const Point& lhs, const Point& rhs) {
    return lhs.x < rhs.x;
}

bool equalPointsPredicate(const Point& lhs, const Point& rhs) {
    return lhs.x == rhs.x;
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
    points.push_back(point);
}

void TableBasedFunction::init() {
    std::sort(points.begin(), points.end(), sortPointsPredicate);
    points.erase(std::unique(points.begin(), points.end(), equalPointsPredicate),
            points.end());
}

const std::vector<Point> TableBasedFunction::getNearestPoints(float arg, int N) const {
//check for 0 size
    int size = points.size();

    if (N > size || N > 3) {
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

    int L = index;
    int R = index + 1;

    std::vector<Point> res;

    float half = 0.5f * (points[L].x + points[R].x);

    if (N == 1) {
        if (arg > half) {
            res.push_back(Point(points[R].x, points[R].y));
        } else {
            res.push_back(Point(points[L].x, points[L].y));
        }
    } else if (N == 2) {
        res.push_back(Point(points[L].x, points[L].y));
        res.push_back(Point(points[R].x, points[R].y));
    } else if (N == 3) {
        if (arg >= half) {
            if (R + 1 < size) {
                res.push_back(Point(points[L].x, points[L].y));
                res.push_back(Point(points[R].x, points[R].y));
                res.push_back(Point(points[R+1].x, points[R+1].y));
            } else {
                res.push_back(Point(points[L-1].x, points[L-1].y));
                res.push_back(Point(points[L].x, points[L].y));
                res.push_back(Point(points[R].x, points[R].y));
            }
        } else {
            if (L - 1 > 0) {
                res.push_back(Point(points[L-1].x, points[L-1].y));
                res.push_back(Point(points[L].x, points[L].y));
                res.push_back(Point(points[R].x, points[R].y));
            } else {
                res.push_back(Point(points[L].x, points[L].y));
                res.push_back(Point(points[R].x, points[R].y));
                res.push_back(Point(points[R+1].x, points[R+1].y));
            }
        }
    } else {
        throw std::exception();
    }

    return res;
}
