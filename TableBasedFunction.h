#ifndef TableBasedFunctionH
#define TableBasedFunctionH

#include <vector>
#include "Point.h"

class TableBasedFunction {
    public:
        explicit TableBasedFunction(int numOfPoints = 0);
        const std::vector<Point>& getPoints() const;
        void appendPoint(const Point& point);
        const std::vector<Point> getNearestPoints(float arg, int N) const;
    private:
        std::vector<Point> points;
};

#endif
