#ifndef TableBasedFunctionH
#define TableBasedFunctionH

#include <vector>
#include "Point.h"

class TableBasedFunction {
    public:
        explicit TableBasedFunction(int numOfPoints = 0);
        const std::vector<Point>& getPoints() const;
        void appendPoint(const Point& point);
        void init();
        const std::vector<Point> getNearestPoints(float arg, int N) const;
    private:
        std::vector<Point> points;
};

bool sortPointsPredicate(const Point& lhs, const Point& rhs);
bool equalPointsPredicate(const Point& lhs, const Point& rhs);

#endif
