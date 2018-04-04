#include "Point.h"

app::Point::Point(float x_, float y_)
    : x(x_), y(y_) {
}

bool app::operator==(const Point& lhs, const Point& rhs) {

    return lhs.x == rhs.x && lhs.y == rhs.y;
}
