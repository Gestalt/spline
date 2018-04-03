#ifndef LagrangePolynomH
#define LagrangePolynomH

#include <vector>

struct Point;

class LagrangePolynom {
public:
    static float solve(const std::vector<Point>& function, float arg, int order);
};

#endif

