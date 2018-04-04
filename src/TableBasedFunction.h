#ifndef TableBasedFunctionH
#define TableBasedFunctionH

#include <vector>

struct Point;

class TableBasedFunction {
    public:
        explicit TableBasedFunction(int numOfPoints = 0);
        void appendPoint(const Point& point);
        const std::vector<Point> getNearestPoints(float arg, unsigned int N) const;
    private:
        std::vector<Point> points;
};

#endif

