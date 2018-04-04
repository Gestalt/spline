#ifndef LagrangePolynomH
#define LagrangePolynomH

#include <vector>

namespace app {

struct Point;

class LagrangePolynom {
public:
    static float solve(const std::vector<Point>& function, float arg, unsigned int order);
};

}
#endif

