#ifndef PointH
#define PointH

namespace app {

struct Point {
    Point(float x_, float y_);

    float x;
    float y;
};

bool operator==(const Point& lhs, const Point& rhs);

}

#endif

